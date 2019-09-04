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
struct TYPE_6__ {int /*<<< orphan*/  ret; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct tegra_bpmp_message {TYPE_3__ rx; TYPE_1__ tx; int /*<<< orphan*/  mrq; } ;
struct tegra_bpmp_channel {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  channel; } ;
struct tegra_bpmp {TYPE_2__ mbox; int /*<<< orphan*/  atomic_tx_lock; struct tegra_bpmp_channel* tx_channel; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  MSG_ACK ; 
 scalar_t__ WARN_ON (int) ; 
 int __tegra_bpmp_channel_read (struct tegra_bpmp_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  mbox_client_txdone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbox_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int tegra_bpmp_channel_write (struct tegra_bpmp_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_bpmp_message_valid (struct tegra_bpmp_message*) ; 
 int tegra_bpmp_wait_ack (struct tegra_bpmp_channel*) ; 

int tegra_bpmp_transfer_atomic(struct tegra_bpmp *bpmp,
			       struct tegra_bpmp_message *msg)
{
	struct tegra_bpmp_channel *channel;
	int err;

	if (WARN_ON(!irqs_disabled()))
		return -EPERM;

	if (!tegra_bpmp_message_valid(msg))
		return -EINVAL;

	channel = bpmp->tx_channel;

	spin_lock(&bpmp->atomic_tx_lock);

	err = tegra_bpmp_channel_write(channel, msg->mrq, MSG_ACK,
				       msg->tx.data, msg->tx.size);
	if (err < 0) {
		spin_unlock(&bpmp->atomic_tx_lock);
		return err;
	}

	spin_unlock(&bpmp->atomic_tx_lock);

	err = mbox_send_message(bpmp->mbox.channel, NULL);
	if (err < 0)
		return err;

	mbox_client_txdone(bpmp->mbox.channel, 0);

	err = tegra_bpmp_wait_ack(channel);
	if (err < 0)
		return err;

	return __tegra_bpmp_channel_read(channel, msg->rx.data, msg->rx.size,
					 &msg->rx.ret);
}