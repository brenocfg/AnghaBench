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
struct sk_buff {int len; scalar_t__ data; } ;
struct qtnf_bus {int dummy; } ;
struct qlink_msg_header {int /*<<< orphan*/  type; int /*<<< orphan*/  len; } ;
struct qlink_event {int dummy; } ;
struct qlink_cmd {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
#define  QLINK_MSG_TYPE_CMDRSP 129 
#define  QLINK_MSG_TYPE_EVENT 128 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int,...) ; 
 int qtnf_trans_event_enqueue (struct qtnf_bus*,struct sk_buff*) ; 
 int /*<<< orphan*/  qtnf_trans_signal_cmdresp (struct qtnf_bus*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int qtnf_trans_handle_rx_ctl_packet(struct qtnf_bus *bus, struct sk_buff *skb)
{
	const struct qlink_msg_header *header = (void *)skb->data;
	int ret = -1;

	if (unlikely(skb->len < sizeof(*header))) {
		pr_warn("packet is too small: %u\n", skb->len);
		dev_kfree_skb(skb);
		return -EINVAL;
	}

	if (unlikely(skb->len != le16_to_cpu(header->len))) {
		pr_warn("cmd reply length mismatch: %u != %u\n",
			skb->len, le16_to_cpu(header->len));
		dev_kfree_skb(skb);
		return -EFAULT;
	}

	switch (le16_to_cpu(header->type)) {
	case QLINK_MSG_TYPE_CMDRSP:
		if (unlikely(skb->len < sizeof(struct qlink_cmd))) {
			pr_warn("cmd reply too short: %u\n", skb->len);
			dev_kfree_skb(skb);
			break;
		}

		qtnf_trans_signal_cmdresp(bus, skb);
		break;
	case QLINK_MSG_TYPE_EVENT:
		if (unlikely(skb->len < sizeof(struct qlink_event))) {
			pr_warn("event too short: %u\n", skb->len);
			dev_kfree_skb(skb);
			break;
		}

		ret = qtnf_trans_event_enqueue(bus, skb);
		break;
	default:
		pr_warn("unknown packet type: %x\n", le16_to_cpu(header->type));
		dev_kfree_skb(skb);
		break;
	}

	return ret;
}