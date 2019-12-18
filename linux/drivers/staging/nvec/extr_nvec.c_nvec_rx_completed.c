#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
struct nvec_chip {int /*<<< orphan*/  rx_work; int /*<<< orphan*/  ec_transfer; TYPE_1__* rx; scalar_t__ state; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  rx_data; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ pos; scalar_t__* data; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 scalar_t__ NVEC_BAT ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvec_msg_free (struct nvec_chip*,TYPE_1__*) ; 
 int /*<<< orphan*/  nvec_msg_is_event (TYPE_1__*) ; 
 scalar_t__ nvec_msg_size (TYPE_1__*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvec_rx_completed(struct nvec_chip *nvec)
{
	if (nvec->rx->pos != nvec_msg_size(nvec->rx)) {
		dev_err(nvec->dev, "RX incomplete: Expected %u bytes, got %u\n",
			(uint)nvec_msg_size(nvec->rx),
			(uint)nvec->rx->pos);

		nvec_msg_free(nvec, nvec->rx);
		nvec->state = 0;

		/* Battery quirk - Often incomplete, and likes to crash */
		if (nvec->rx->data[0] == NVEC_BAT)
			complete(&nvec->ec_transfer);

		return;
	}

	spin_lock(&nvec->rx_lock);

	/*
	 * Add the received data to the work list and move the ring buffer
	 * pointer to the next entry.
	 */
	list_add_tail(&nvec->rx->node, &nvec->rx_data);

	spin_unlock(&nvec->rx_lock);

	nvec->state = 0;

	if (!nvec_msg_is_event(nvec->rx))
		complete(&nvec->ec_transfer);

	schedule_work(&nvec->rx_work);
}