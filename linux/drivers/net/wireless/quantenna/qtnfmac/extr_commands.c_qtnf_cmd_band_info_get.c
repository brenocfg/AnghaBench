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
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ data; } ;
struct qtnf_wmac {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; } ;
struct qlink_resp_band_info_get {scalar_t__ band; } ;
struct qlink_cmd_band_info_get {scalar_t__ band; } ;
struct ieee80211_supported_band {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_BAND_INFO_GET ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ qlink_utils_band_cfg2q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_resp_fill_band_info (struct ieee80211_supported_band*,struct qlink_resp_band_info_get*,size_t) ; 
 int qtnf_cmd_send_with_reply (int /*<<< orphan*/ ,struct sk_buff*,struct sk_buff**,int,size_t*) ; 

int qtnf_cmd_band_info_get(struct qtnf_wmac *mac,
			   struct ieee80211_supported_band *band)
{
	struct sk_buff *cmd_skb, *resp_skb = NULL;
	struct qlink_cmd_band_info_get *cmd;
	struct qlink_resp_band_info_get *resp;
	size_t info_len = 0;
	int ret = 0;
	u8 qband = qlink_utils_band_cfg2q(band->band);

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, 0,
					    QLINK_CMD_BAND_INFO_GET,
					    sizeof(*cmd));
	if (!cmd_skb)
		return -ENOMEM;

	cmd = (struct qlink_cmd_band_info_get *)cmd_skb->data;
	cmd->band = qband;

	qtnf_bus_lock(mac->bus);
	ret = qtnf_cmd_send_with_reply(mac->bus, cmd_skb, &resp_skb,
				       sizeof(*resp), &info_len);
	if (ret)
		goto out;

	resp = (struct qlink_resp_band_info_get *)resp_skb->data;
	if (resp->band != qband) {
		pr_err("MAC%u: reply band %u != cmd band %u\n", mac->macid,
		       resp->band, qband);
		ret = -EINVAL;
		goto out;
	}

	ret = qtnf_cmd_resp_fill_band_info(band, resp, info_len);

out:
	qtnf_bus_unlock(mac->bus);
	consume_skb(resp_skb);

	return ret;
}