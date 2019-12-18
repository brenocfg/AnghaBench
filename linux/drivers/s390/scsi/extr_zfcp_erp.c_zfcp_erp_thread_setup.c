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
struct zfcp_adapter {struct task_struct* erp_thread; TYPE_1__* ccw_device; } ;
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct zfcp_adapter*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_thread ; 

int zfcp_erp_thread_setup(struct zfcp_adapter *adapter)
{
	struct task_struct *thread;

	thread = kthread_run(zfcp_erp_thread, adapter, "zfcperp%s",
			     dev_name(&adapter->ccw_device->dev));
	if (IS_ERR(thread)) {
		dev_err(&adapter->ccw_device->dev,
			"Creating an ERP thread for the FCP device failed.\n");
		return PTR_ERR(thread);
	}

	adapter->erp_thread = thread;
	return 0;
}