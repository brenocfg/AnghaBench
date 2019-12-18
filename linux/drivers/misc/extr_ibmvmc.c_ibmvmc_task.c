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
struct vio_dev {int dummy; } ;
struct ibmvmc_crq_msg {int valid; } ;
struct crq_server_adapter {int /*<<< orphan*/  queue; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 struct ibmvmc_crq_msg* crq_queue_next_crq (int /*<<< orphan*/ *) ; 
 TYPE_1__ ibmvmc ; 
 int /*<<< orphan*/  ibmvmc_handle_crq (struct ibmvmc_crq_msg*,struct crq_server_adapter*) ; 
 scalar_t__ ibmvmc_state_sched_reset ; 
 struct vio_dev* to_vio_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vio_disable_interrupts (struct vio_dev*) ; 
 int /*<<< orphan*/  vio_enable_interrupts (struct vio_dev*) ; 

__attribute__((used)) static void ibmvmc_task(unsigned long data)
{
	struct crq_server_adapter *adapter =
		(struct crq_server_adapter *)data;
	struct vio_dev *vdev = to_vio_dev(adapter->dev);
	struct ibmvmc_crq_msg *crq;
	int done = 0;

	while (!done) {
		/* Pull all the valid messages off the CRQ */
		while ((crq = crq_queue_next_crq(&adapter->queue)) != NULL) {
			ibmvmc_handle_crq(crq, adapter);
			crq->valid = 0x00;
			/* CRQ reset was requested, stop processing CRQs.
			 * Interrupts will be re-enabled by the reset task.
			 */
			if (ibmvmc.state == ibmvmc_state_sched_reset)
				return;
		}

		vio_enable_interrupts(vdev);
		crq = crq_queue_next_crq(&adapter->queue);
		if (crq) {
			vio_disable_interrupts(vdev);
			ibmvmc_handle_crq(crq, adapter);
			crq->valid = 0x00;
			/* CRQ reset was requested, stop processing CRQs.
			 * Interrupts will be re-enabled by the reset task.
			 */
			if (ibmvmc.state == ibmvmc_state_sched_reset)
				return;
		} else {
			done = 1;
		}
	}
}