#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int f_flags; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_5__ {scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_4__ {scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  users; TYPE_2__ in_crc; TYPE_1__ out_crc; } ;

/* Variables and functions */
 int ACPI_AML_CLOSED ; 
 int ACPI_AML_OPENED ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int O_ACCMODE ; 
 int O_WRONLY ; 
 struct file* acpi_aml_active_reader ; 
 TYPE_3__ acpi_aml_io ; 
 int /*<<< orphan*/  acpi_initialize_debugger () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int acpi_aml_open(struct inode *inode, struct file *file)
{
	int ret = 0;
	acpi_status status;

	mutex_lock(&acpi_aml_io.lock);
	/*
	 * The debugger interface is being closed, no new user is allowed
	 * during this period.
	 */
	if (acpi_aml_io.flags & ACPI_AML_CLOSED) {
		ret = -EBUSY;
		goto err_lock;
	}
	if ((file->f_flags & O_ACCMODE) != O_WRONLY) {
		/*
		 * Only one reader is allowed to initiate the debugger
		 * thread.
		 */
		if (acpi_aml_active_reader) {
			ret = -EBUSY;
			goto err_lock;
		} else {
			pr_debug("Opening debugger reader.\n");
			acpi_aml_active_reader = file;
		}
	} else {
		/*
		 * No writer is allowed unless the debugger thread is
		 * ready.
		 */
		if (!(acpi_aml_io.flags & ACPI_AML_OPENED)) {
			ret = -ENODEV;
			goto err_lock;
		}
	}
	if (acpi_aml_active_reader == file) {
		pr_debug("Opening debugger interface.\n");
		mutex_unlock(&acpi_aml_io.lock);

		pr_debug("Initializing debugger thread.\n");
		status = acpi_initialize_debugger();
		if (ACPI_FAILURE(status)) {
			pr_err("Failed to initialize debugger.\n");
			ret = -EINVAL;
			goto err_exit;
		}
		pr_debug("Debugger thread initialized.\n");

		mutex_lock(&acpi_aml_io.lock);
		acpi_aml_io.flags |= ACPI_AML_OPENED;
		acpi_aml_io.out_crc.head = acpi_aml_io.out_crc.tail = 0;
		acpi_aml_io.in_crc.head = acpi_aml_io.in_crc.tail = 0;
		pr_debug("Debugger interface opened.\n");
	}
	acpi_aml_io.users++;
err_lock:
	if (ret < 0) {
		if (acpi_aml_active_reader == file)
			acpi_aml_active_reader = NULL;
	}
	mutex_unlock(&acpi_aml_io.lock);
err_exit:
	return ret;
}