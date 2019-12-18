#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rockchip_mbox_msg {int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {int num_chans; int /*<<< orphan*/  dev; int /*<<< orphan*/ * chans; } ;
struct rockchip_mbox {TYPE_2__ mbox; TYPE_1__* chans; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int irq; struct rockchip_mbox_msg* msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mbox_chan_received_data (int /*<<< orphan*/ *,struct rockchip_mbox_msg*) ; 

__attribute__((used)) static irqreturn_t rockchip_mbox_isr(int irq, void *dev_id)
{
	int idx;
	struct rockchip_mbox_msg *msg = NULL;
	struct rockchip_mbox *mb = (struct rockchip_mbox *)dev_id;

	for (idx = 0; idx < mb->mbox.num_chans; idx++) {
		if (irq != mb->chans[idx].irq)
			continue;

		msg = mb->chans[idx].msg;
		if (!msg) {
			dev_err(mb->mbox.dev,
				"Chan[%d]: B2A message is NULL\n", idx);
			break; /* spurious */
		}

		mbox_chan_received_data(&mb->mbox.chans[idx], msg);
		mb->chans[idx].msg = NULL;

		dev_dbg(mb->mbox.dev, "Chan[%d]: B2A message, cmd 0x%08x\n",
			idx, msg->cmd);

		break;
	}

	return IRQ_HANDLED;
}