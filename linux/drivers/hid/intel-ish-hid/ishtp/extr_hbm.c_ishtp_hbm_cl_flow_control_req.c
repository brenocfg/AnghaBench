#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ishtp_msg_hdr {int dummy; } ;
struct ishtp_device {int dummy; } ;
struct ishtp_cl {int /*<<< orphan*/  fc_spinlock; int /*<<< orphan*/  err_send_fc; int /*<<< orphan*/  ts_max_fc_delay; scalar_t__ ts_rx; int /*<<< orphan*/  ts_out_fc; int /*<<< orphan*/  out_flow_ctrl_cnt; scalar_t__ out_flow_ctrl_creds; scalar_t__ recv_msg_num_frags; } ;
struct hbm_flow_control {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;
typedef  int /*<<< orphan*/  flow_ctrl ;

/* Variables and functions */
 int /*<<< orphan*/  ISHTP_FLOW_CONTROL_CMD ; 
 int /*<<< orphan*/  ishtp_hbm_cl_hdr (struct ishtp_cl*,int /*<<< orphan*/ ,struct hbm_flow_control*,size_t const) ; 
 int /*<<< orphan*/  ishtp_hbm_hdr (struct ishtp_msg_hdr*,size_t const) ; 
 int ishtp_write_message (struct ishtp_device*,struct ishtp_msg_hdr*,struct hbm_flow_control*) ; 
 scalar_t__ ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ishtp_hbm_cl_flow_control_req(struct ishtp_device *dev,
				  struct ishtp_cl *cl)
{
	struct ishtp_msg_hdr hdr;
	struct hbm_flow_control flow_ctrl;
	const size_t len = sizeof(flow_ctrl);
	int	rv;
	unsigned long	flags;

	spin_lock_irqsave(&cl->fc_spinlock, flags);

	ishtp_hbm_hdr(&hdr, len);
	ishtp_hbm_cl_hdr(cl, ISHTP_FLOW_CONTROL_CMD, &flow_ctrl, len);

	/*
	 * Sync possible race when RB recycle and packet receive paths
	 * both try to send an out FC
	 */
	if (cl->out_flow_ctrl_creds) {
		spin_unlock_irqrestore(&cl->fc_spinlock, flags);
		return	0;
	}

	cl->recv_msg_num_frags = 0;

	rv = ishtp_write_message(dev, &hdr, &flow_ctrl);
	if (!rv) {
		++cl->out_flow_ctrl_creds;
		++cl->out_flow_ctrl_cnt;
		cl->ts_out_fc = ktime_get();
		if (cl->ts_rx) {
			ktime_t ts_diff = ktime_sub(cl->ts_out_fc, cl->ts_rx);
			if (ktime_after(ts_diff, cl->ts_max_fc_delay))
				cl->ts_max_fc_delay = ts_diff;
		}
	} else {
		++cl->err_send_fc;
	}

	spin_unlock_irqrestore(&cl->fc_spinlock, flags);
	return	rv;
}