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
struct most_interface {int dummy; } ;
struct mbo {int /*<<< orphan*/  (* complete ) (struct mbo*) ;int /*<<< orphan*/  status; scalar_t__ buffer_length; scalar_t__ processed_length; int /*<<< orphan*/  virt_address; int /*<<< orphan*/  list; } ;
struct TYPE_6__ {int /*<<< orphan*/  work; } ;
struct TYPE_4__ {TYPE_3__ dwork; scalar_t__ int_disabled; int /*<<< orphan*/  list; } ;
struct hdm_i2c {TYPE_2__* client; TYPE_1__ rx; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CH_RX ; 
 int /*<<< orphan*/  MBO_E_INVAL ; 
 int /*<<< orphan*/  MBO_SUCCESS ; 
 int NUM_CHANNELS ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (TYPE_3__*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int i2c_master_send (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pending_rx_work (int /*<<< orphan*/ *) ; 
 scalar_t__ polling_rate ; 
 int /*<<< orphan*/  stub1 (struct mbo*) ; 
 struct hdm_i2c* to_hdm (struct most_interface*) ; 

__attribute__((used)) static int enqueue(struct most_interface *most_iface,
		   int ch_idx, struct mbo *mbo)
{
	struct hdm_i2c *dev = to_hdm(most_iface);
	int ret;

	BUG_ON(ch_idx < 0 || ch_idx >= NUM_CHANNELS);

	if (ch_idx == CH_RX) {
		/* RX */
		if (!polling_rate)
			disable_irq(dev->client->irq);
		cancel_delayed_work_sync(&dev->rx.dwork);
		list_add_tail(&mbo->list, &dev->rx.list);
		if (dev->rx.int_disabled || polling_rate)
			pending_rx_work(&dev->rx.dwork.work);
		if (!polling_rate)
			enable_irq(dev->client->irq);
	} else {
		/* TX */
		ret = i2c_master_send(dev->client, mbo->virt_address,
				      mbo->buffer_length);
		if (ret <= 0) {
			mbo->processed_length = 0;
			mbo->status = MBO_E_INVAL;
		} else {
			mbo->processed_length = mbo->buffer_length;
			mbo->status = MBO_SUCCESS;
		}
		mbo->complete(mbo);
	}

	return 0;
}