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
struct sk_buff {int dummy; } ;
struct i2400m_l3l4_hdr {int /*<<< orphan*/  type; } ;
struct i2400m {int /*<<< orphan*/  wimax_dev; int /*<<< orphan*/  trace_msg_from_user; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int I2400M_MT_REPORT_MASK ; 
 int /*<<< orphan*/  d_dump (int,struct device*,struct i2400m_l3l4_hdr const*,size_t) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,char*,unsigned int,size_t) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int i2400m_msg_size_check (struct i2400m*,struct i2400m_l3l4_hdr const*,size_t) ; 
 int /*<<< orphan*/  i2400m_report_hook_queue (struct i2400m*,struct sk_buff*,struct i2400m_l3l4_hdr const*,size_t) ; 
 int /*<<< orphan*/  i2400m_rx_ctl_ack (struct i2400m*,void const*,size_t) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int wimax_msg (int /*<<< orphan*/ *,char*,struct i2400m_l3l4_hdr const*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void i2400m_rx_ctl(struct i2400m *i2400m, struct sk_buff *skb_rx,
		   const void *payload, size_t size)
{
	int result;
	struct device *dev = i2400m_dev(i2400m);
	const struct i2400m_l3l4_hdr *l3l4_hdr = payload;
	unsigned msg_type;

	result = i2400m_msg_size_check(i2400m, l3l4_hdr, size);
	if (result < 0) {
		dev_err(dev, "HW BUG? device sent a bad message: %d\n",
			result);
		goto error_check;
	}
	msg_type = le16_to_cpu(l3l4_hdr->type);
	d_printf(1, dev, "%s 0x%04x: %zu bytes\n",
		 msg_type & I2400M_MT_REPORT_MASK ? "REPORT" : "CMD/SET/GET",
		 msg_type, size);
	d_dump(2, dev, l3l4_hdr, size);
	if (msg_type & I2400M_MT_REPORT_MASK) {
		/*
		 * Process each report
		 *
		 * - has to be ran serialized as well
		 *
		 * - the handling might force the execution of
		 *   commands. That might cause reentrancy issues with
		 *   bus-specific subdrivers and workqueues, so the we
		 *   run it in a separate workqueue.
		 *
		 * - when the driver is not yet ready to handle them,
		 *   they are queued and at some point the queue is
		 *   restarted [NOTE: we can't queue SKBs directly, as
		 *   this might be a piece of a SKB, not the whole
		 *   thing, and this is cheaper than cloning the
		 *   SKB].
		 *
		 * Note we don't do refcounting for the device
		 * structure; this is because before destroying
		 * 'i2400m', we make sure to flush the
		 * i2400m->work_queue, so there are no issues.
		 */
		i2400m_report_hook_queue(i2400m, skb_rx, l3l4_hdr, size);
		if (unlikely(i2400m->trace_msg_from_user))
			wimax_msg(&i2400m->wimax_dev, "echo",
				  l3l4_hdr, size, GFP_KERNEL);
		result = wimax_msg(&i2400m->wimax_dev, NULL, l3l4_hdr, size,
				   GFP_KERNEL);
		if (result < 0)
			dev_err(dev, "error sending report to userspace: %d\n",
				result);
	} else		/* an ack to a CMD, GET or SET */
		i2400m_rx_ctl_ack(i2400m, payload, size);
error_check:
	return;
}