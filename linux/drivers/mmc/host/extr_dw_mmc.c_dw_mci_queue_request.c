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
struct mmc_request {int dummy; } ;
struct dw_mci_slot {int /*<<< orphan*/  queue_node; TYPE_1__* mmc; struct mmc_request* mrq; } ;
struct dw_mci {scalar_t__ state; int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 scalar_t__ STATE_IDLE ; 
 scalar_t__ STATE_SENDING_CMD ; 
 scalar_t__ STATE_WAITING_CMD11_DONE ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dw_mci_start_request (struct dw_mci*,struct dw_mci_slot*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dw_mci_queue_request(struct dw_mci *host, struct dw_mci_slot *slot,
				 struct mmc_request *mrq)
{
	dev_vdbg(&slot->mmc->class_dev, "queue request: state=%d\n",
		 host->state);

	slot->mrq = mrq;

	if (host->state == STATE_WAITING_CMD11_DONE) {
		dev_warn(&slot->mmc->class_dev,
			 "Voltage change didn't complete\n");
		/*
		 * this case isn't expected to happen, so we can
		 * either crash here or just try to continue on
		 * in the closest possible state
		 */
		host->state = STATE_IDLE;
	}

	if (host->state == STATE_IDLE) {
		host->state = STATE_SENDING_CMD;
		dw_mci_start_request(host, slot);
	} else {
		list_add_tail(&slot->queue_node, &host->queue);
	}
}