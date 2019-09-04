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
struct crq_server_adapter {int /*<<< orphan*/  work_task; int /*<<< orphan*/  dev; int /*<<< orphan*/  reset_wait_queue; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int H_RESOURCE ; 
 int H_SUCCESS ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ ibmvmc ; 
 int ibmvmc_reset_crq_queue (struct crq_server_adapter*) ; 
 scalar_t__ ibmvmc_send_crq (struct crq_server_adapter*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ibmvmc_state_crqinit ; 
 scalar_t__ ibmvmc_state_failed ; 
 scalar_t__ ibmvmc_state_sched_reset ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_vio_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vio_enable_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ibmvmc_reset_task(void *data)
{
	struct crq_server_adapter *adapter = data;
	int rc;

	set_user_nice(current, -20);

	while (!kthread_should_stop()) {
		wait_event_interruptible(adapter->reset_wait_queue,
			(ibmvmc.state == ibmvmc_state_sched_reset) ||
			kthread_should_stop());

		if (kthread_should_stop())
			break;

		dev_dbg(adapter->dev, "CRQ resetting in process context");
		tasklet_disable(&adapter->work_task);

		rc = ibmvmc_reset_crq_queue(adapter);

		if (rc != H_SUCCESS && rc != H_RESOURCE) {
			dev_err(adapter->dev, "Error initializing CRQ.  rc = 0x%x\n",
				rc);
			ibmvmc.state = ibmvmc_state_failed;
		} else {
			ibmvmc.state = ibmvmc_state_crqinit;

			if (ibmvmc_send_crq(adapter, 0xC001000000000000LL, 0)
			    != 0 && rc != H_RESOURCE)
				dev_warn(adapter->dev, "Failed to send initialize CRQ message\n");
		}

		vio_enable_interrupts(to_vio_dev(adapter->dev));
		tasklet_enable(&adapter->work_task);
	}

	return 0;
}