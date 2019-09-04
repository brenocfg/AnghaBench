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
struct task_struct {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_thread_id ;
typedef  int /*<<< orphan*/  acpi_osd_exec_callback ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct task_struct* thread; void* context; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 TYPE_1__ acpi_aml_io ; 
 int /*<<< orphan*/  acpi_aml_thread ; 
 int /*<<< orphan*/  acpi_set_debugger_thread_id (int /*<<< orphan*/ ) ; 
 struct task_struct* kthread_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static int acpi_aml_create_thread(acpi_osd_exec_callback function, void *context)
{
	struct task_struct *t;

	mutex_lock(&acpi_aml_io.lock);
	acpi_aml_io.function = function;
	acpi_aml_io.context = context;
	mutex_unlock(&acpi_aml_io.lock);

	t = kthread_create(acpi_aml_thread, NULL, "aml");
	if (IS_ERR(t)) {
		pr_err("Failed to create AML debugger thread.\n");
		return PTR_ERR(t);
	}

	mutex_lock(&acpi_aml_io.lock);
	acpi_aml_io.thread = t;
	acpi_set_debugger_thread_id((acpi_thread_id)(unsigned long)t);
	wake_up_process(t);
	mutex_unlock(&acpi_aml_io.lock);
	return 0;
}