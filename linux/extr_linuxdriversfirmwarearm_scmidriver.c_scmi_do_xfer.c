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
struct TYPE_4__ {scalar_t__ status; scalar_t__ poll_completion; int /*<<< orphan*/  protocol_id; } ;
struct scmi_xfer {TYPE_2__ hdr; int /*<<< orphan*/  done; } ;
struct scmi_info {TYPE_1__* desc; int /*<<< orphan*/  tx_idr; struct device* dev; } ;
struct scmi_handle {int dummy; } ;
struct scmi_chan_info {int /*<<< orphan*/  chan; int /*<<< orphan*/  payload; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_3__ {int /*<<< orphan*/  max_rx_timeout_ms; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SCMI_MAX_POLL_TO_NS ; 
 scalar_t__ _RET_IP_ ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,void*) ; 
 struct scmi_info* handle_to_scmi_info (struct scmi_handle const*) ; 
 struct scmi_chan_info* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mbox_client_txdone (int /*<<< orphan*/ ,int) ; 
 int mbox_send_message (int /*<<< orphan*/ ,struct scmi_xfer*) ; 
 int msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scmi_fetch_response (struct scmi_xfer*,int /*<<< orphan*/ ) ; 
 int scmi_to_linux_errno (scalar_t__) ; 
 int /*<<< orphan*/  scmi_xfer_done_no_timeout (struct scmi_chan_info*,struct scmi_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_until_cond (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

int scmi_do_xfer(const struct scmi_handle *handle, struct scmi_xfer *xfer)
{
	int ret;
	int timeout;
	struct scmi_info *info = handle_to_scmi_info(handle);
	struct device *dev = info->dev;
	struct scmi_chan_info *cinfo;

	cinfo = idr_find(&info->tx_idr, xfer->hdr.protocol_id);
	if (unlikely(!cinfo))
		return -EINVAL;

	ret = mbox_send_message(cinfo->chan, xfer);
	if (ret < 0) {
		dev_dbg(dev, "mbox send fail %d\n", ret);
		return ret;
	}

	/* mbox_send_message returns non-negative value on success, so reset */
	ret = 0;

	if (xfer->hdr.poll_completion) {
		ktime_t stop = ktime_add_ns(ktime_get(), SCMI_MAX_POLL_TO_NS);

		spin_until_cond(scmi_xfer_done_no_timeout(cinfo, xfer, stop));

		if (ktime_before(ktime_get(), stop))
			scmi_fetch_response(xfer, cinfo->payload);
		else
			ret = -ETIMEDOUT;
	} else {
		/* And we wait for the response. */
		timeout = msecs_to_jiffies(info->desc->max_rx_timeout_ms);
		if (!wait_for_completion_timeout(&xfer->done, timeout)) {
			dev_err(dev, "mbox timed out in resp(caller: %pS)\n",
				(void *)_RET_IP_);
			ret = -ETIMEDOUT;
		}
	}

	if (!ret && xfer->hdr.status)
		ret = scmi_to_linux_errno(xfer->hdr.status);

	/*
	 * NOTE: we might prefer not to need the mailbox ticker to manage the
	 * transfer queueing since the protocol layer queues things by itself.
	 * Unfortunately, we have to kick the mailbox framework after we have
	 * received our message.
	 */
	mbox_client_txdone(cinfo->chan, ret);

	return ret;
}