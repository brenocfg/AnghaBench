#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ users; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_AML_CLOSED ; 
 int /*<<< orphan*/  ACPI_AML_OPENED ; 
 struct file* acpi_aml_active_reader ; 
 int /*<<< orphan*/  acpi_aml_busy () ; 
 TYPE_1__ acpi_aml_io ; 
 int /*<<< orphan*/  acpi_aml_used () ; 
 int /*<<< orphan*/  acpi_terminate_debugger () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acpi_aml_release(struct inode *inode, struct file *file)
{
	mutex_lock(&acpi_aml_io.lock);
	acpi_aml_io.users--;
	if (file == acpi_aml_active_reader) {
		pr_debug("Closing debugger reader.\n");
		acpi_aml_active_reader = NULL;

		pr_debug("Closing debugger interface.\n");
		acpi_aml_io.flags |= ACPI_AML_CLOSED;

		/*
		 * Wake up all user space/kernel space blocked
		 * readers/writers.
		 */
		wake_up_interruptible(&acpi_aml_io.wait);
		mutex_unlock(&acpi_aml_io.lock);
		/*
		 * Wait all user space/kernel space readers/writers to
		 * stop so that ACPICA command loop of the debugger thread
		 * should fail all its command line reads after this point.
		 */
		wait_event(acpi_aml_io.wait, !acpi_aml_busy());

		/*
		 * Then we try to terminate the debugger thread if it is
		 * not terminated.
		 */
		pr_debug("Terminating debugger thread.\n");
		acpi_terminate_debugger();
		wait_event(acpi_aml_io.wait, !acpi_aml_used());
		pr_debug("Debugger thread terminated.\n");

		mutex_lock(&acpi_aml_io.lock);
		acpi_aml_io.flags &= ~ACPI_AML_OPENED;
	}
	if (acpi_aml_io.users == 0) {
		pr_debug("Debugger interface closed.\n");
		acpi_aml_io.flags &= ~ACPI_AML_CLOSED;
	}
	mutex_unlock(&acpi_aml_io.lock);
	return 0;
}