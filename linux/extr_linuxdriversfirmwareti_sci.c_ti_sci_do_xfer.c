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
struct ti_sci_xfer {int /*<<< orphan*/  done; int /*<<< orphan*/  tx_message; } ;
struct ti_sci_info {int /*<<< orphan*/  chan_tx; TYPE_1__* desc; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_rx_timeout_ms; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ _RET_IP_ ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,void*) ; 
 int /*<<< orphan*/  mbox_client_txdone (int /*<<< orphan*/ ,int) ; 
 int mbox_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int ti_sci_do_xfer(struct ti_sci_info *info,
				 struct ti_sci_xfer *xfer)
{
	int ret;
	int timeout;
	struct device *dev = info->dev;

	ret = mbox_send_message(info->chan_tx, &xfer->tx_message);
	if (ret < 0)
		return ret;

	ret = 0;

	/* And we wait for the response. */
	timeout = msecs_to_jiffies(info->desc->max_rx_timeout_ms);
	if (!wait_for_completion_timeout(&xfer->done, timeout)) {
		dev_err(dev, "Mbox timedout in resp(caller: %pS)\n",
			(void *)_RET_IP_);
		ret = -ETIMEDOUT;
	}
	/*
	 * NOTE: we might prefer not to need the mailbox ticker to manage the
	 * transfer queueing since the protocol layer queues things by itself.
	 * Unfortunately, we have to kick the mailbox framework after we have
	 * received our message.
	 */
	mbox_client_txdone(info->chan_tx, ret);

	return ret;
}