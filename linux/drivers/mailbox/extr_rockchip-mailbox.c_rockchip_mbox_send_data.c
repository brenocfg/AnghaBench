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
struct rockchip_mbox_msg {scalar_t__ rx_size; scalar_t__ cmd; } ;
struct rockchip_mbox_chan {size_t idx; struct rockchip_mbox_msg* msg; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct rockchip_mbox {scalar_t__ buf_size; scalar_t__ mbox_base; struct rockchip_mbox_chan* chans; TYPE_2__ mbox; } ;
struct mbox_chan {TYPE_1__* mbox; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAILBOX_A2B_CMD (size_t) ; 
 scalar_t__ MAILBOX_A2B_DAT (size_t) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 struct rockchip_mbox* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int rockchip_mbox_send_data(struct mbox_chan *chan, void *data)
{
	struct rockchip_mbox *mb = dev_get_drvdata(chan->mbox->dev);
	struct rockchip_mbox_msg *msg = data;
	struct rockchip_mbox_chan *chans = mb->chans;

	if (!msg)
		return -EINVAL;

	if (msg->rx_size > mb->buf_size) {
		dev_err(mb->mbox.dev, "Transmit size over buf size(%d)\n",
			mb->buf_size);
		return -EINVAL;
	}

	dev_dbg(mb->mbox.dev, "Chan[%d]: A2B message, cmd 0x%08x\n",
		chans->idx, msg->cmd);

	mb->chans[chans->idx].msg = msg;

	writel_relaxed(msg->cmd, mb->mbox_base + MAILBOX_A2B_CMD(chans->idx));
	writel_relaxed(msg->rx_size, mb->mbox_base +
		       MAILBOX_A2B_DAT(chans->idx));

	return 0;
}