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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
struct qtnf_wmac {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; } ;
struct qtnf_chan_stats {int dummy; } ;
struct qlink_resp_get_chan_stats {int /*<<< orphan*/  info; } ;
struct qlink_cmd_get_chan_stats {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_CHAN_STATS ; 
 int /*<<< orphan*/  QLINK_VIFID_RSVD ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_resp_proc_chan_stat_info (struct qtnf_chan_stats*,int /*<<< orphan*/ ,size_t) ; 
 int qtnf_cmd_send_with_reply (int /*<<< orphan*/ ,struct sk_buff*,struct sk_buff**,int,size_t*) ; 

int qtnf_cmd_get_chan_stats(struct qtnf_wmac *mac, u16 channel,
			    struct qtnf_chan_stats *stats)
{
	struct sk_buff *cmd_skb, *resp_skb = NULL;
	struct qlink_cmd_get_chan_stats *cmd;
	struct qlink_resp_get_chan_stats *resp;
	size_t var_data_len = 0;
	int ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, QLINK_VIFID_RSVD,
					    QLINK_CMD_CHAN_STATS,
					    sizeof(*cmd));
	if (!cmd_skb)
		return -ENOMEM;

	qtnf_bus_lock(mac->bus);

	cmd = (struct qlink_cmd_get_chan_stats *)cmd_skb->data;
	cmd->channel = cpu_to_le16(channel);

	ret = qtnf_cmd_send_with_reply(mac->bus, cmd_skb, &resp_skb,
				       sizeof(*resp), &var_data_len);
	if (ret)
		goto out;

	resp = (struct qlink_resp_get_chan_stats *)resp_skb->data;
	ret = qtnf_cmd_resp_proc_chan_stat_info(stats, resp->info,
						var_data_len);

out:
	qtnf_bus_unlock(mac->bus);
	consume_skb(resp_skb);

	return ret;
}