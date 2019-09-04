#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  ret; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct tegra_bpmp_message {TYPE_6__ rx; TYPE_1__ tx; int /*<<< orphan*/  mrq; } ;
struct tegra_bpmp_channel {int /*<<< orphan*/  completion; } ;
struct TYPE_8__ {int /*<<< orphan*/  channel; } ;
struct tegra_bpmp {TYPE_5__* soc; TYPE_2__ mbox; } ;
struct TYPE_9__ {int /*<<< orphan*/  timeout; } ;
struct TYPE_10__ {TYPE_3__ thread; } ;
struct TYPE_11__ {TYPE_4__ channels; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int ETIMEDOUT ; 
 scalar_t__ IS_ERR (struct tegra_bpmp_channel*) ; 
 int PTR_ERR (struct tegra_bpmp_channel*) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  mbox_client_txdone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbox_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tegra_bpmp_channel_read (struct tegra_bpmp_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_bpmp_message_valid (struct tegra_bpmp_message*) ; 
 struct tegra_bpmp_channel* tegra_bpmp_write_threaded (struct tegra_bpmp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,unsigned long) ; 

int tegra_bpmp_transfer(struct tegra_bpmp *bpmp,
			struct tegra_bpmp_message *msg)
{
	struct tegra_bpmp_channel *channel;
	unsigned long timeout;
	int err;

	if (WARN_ON(irqs_disabled()))
		return -EPERM;

	if (!tegra_bpmp_message_valid(msg))
		return -EINVAL;

	channel = tegra_bpmp_write_threaded(bpmp, msg->mrq, msg->tx.data,
					    msg->tx.size);
	if (IS_ERR(channel))
		return PTR_ERR(channel);

	err = mbox_send_message(bpmp->mbox.channel, NULL);
	if (err < 0)
		return err;

	mbox_client_txdone(bpmp->mbox.channel, 0);

	timeout = usecs_to_jiffies(bpmp->soc->channels.thread.timeout);

	err = wait_for_completion_timeout(&channel->completion, timeout);
	if (err == 0)
		return -ETIMEDOUT;

	return tegra_bpmp_channel_read(channel, msg->rx.data, msg->rx.size,
				       &msg->rx.ret);
}