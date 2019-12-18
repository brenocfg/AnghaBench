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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ data; } ;
struct htt_stats_req {void* cookie_msb; void* cookie_lsb; int /*<<< orphan*/  stat_type; int /*<<< orphan*/  reset_types; int /*<<< orphan*/  upload_types; } ;
struct TYPE_2__ {int /*<<< orphan*/  msg_type; } ;
struct htt_cmd {struct htt_stats_req stats_req; TYPE_1__ hdr; } ;
struct ath10k_htt {int /*<<< orphan*/  eid; struct ath10k* ar; } ;
struct ath10k {int /*<<< orphan*/  htc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HTT_H2T_MSG_TYPE_STATS_REQ ; 
 int /*<<< orphan*/  HTT_STATS_REQ_CFG_STAT_TYPE_INVALID ; 
 struct sk_buff* ath10k_htc_alloc_skb (struct ath10k*,int) ; 
 int ath10k_htc_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct htt_stats_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

int ath10k_htt_h2t_stats_req(struct ath10k_htt *htt, u32 mask, u32 reset_mask,
			     u64 cookie)
{
	struct ath10k *ar = htt->ar;
	struct htt_stats_req *req;
	struct sk_buff *skb;
	struct htt_cmd *cmd;
	int len = 0, ret;

	len += sizeof(cmd->hdr);
	len += sizeof(cmd->stats_req);

	skb = ath10k_htc_alloc_skb(ar, len);
	if (!skb)
		return -ENOMEM;

	skb_put(skb, len);
	cmd = (struct htt_cmd *)skb->data;
	cmd->hdr.msg_type = HTT_H2T_MSG_TYPE_STATS_REQ;

	req = &cmd->stats_req;

	memset(req, 0, sizeof(*req));

	/* currently we support only max 24 bit masks so no need to worry
	 * about endian support
	 */
	memcpy(req->upload_types, &mask, 3);
	memcpy(req->reset_types, &reset_mask, 3);
	req->stat_type = HTT_STATS_REQ_CFG_STAT_TYPE_INVALID;
	req->cookie_lsb = cpu_to_le32(cookie & 0xffffffff);
	req->cookie_msb = cpu_to_le32((cookie & 0xffffffff00000000ULL) >> 32);

	ret = ath10k_htc_send(&htt->ar->htc, htt->eid, skb);
	if (ret) {
		ath10k_warn(ar, "failed to send htt type stats request: %d",
			    ret);
		dev_kfree_skb_any(skb);
		return ret;
	}

	return 0;
}