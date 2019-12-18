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
typedef  int u32 ;
struct wiphy {int /*<<< orphan*/  retry_short; int /*<<< orphan*/  retry_long; int /*<<< orphan*/  coverage_class; int /*<<< orphan*/  rts_threshold; int /*<<< orphan*/  frag_threshold; } ;
struct sk_buff {int dummy; } ;
struct qtnf_wmac {int /*<<< orphan*/  bus; int /*<<< orphan*/  macid; } ;
struct qlink_cmd {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QLINK_CMD_PHY_PARAMS_SET ; 
 int /*<<< orphan*/  QTN_TLV_ID_COVERAGE_CLASS ; 
 int /*<<< orphan*/  QTN_TLV_ID_FRAG_THRESH ; 
 int /*<<< orphan*/  QTN_TLV_ID_LRETRY_LIMIT ; 
 int /*<<< orphan*/  QTN_TLV_ID_RTS_THRESH ; 
 int /*<<< orphan*/  QTN_TLV_ID_SRETRY_LIMIT ; 
 int WIPHY_PARAM_COVERAGE_CLASS ; 
 int WIPHY_PARAM_FRAG_THRESHOLD ; 
 int WIPHY_PARAM_RETRY_LONG ; 
 int WIPHY_PARAM_RETRY_SHORT ; 
 int WIPHY_PARAM_RTS_THRESHOLD ; 
 struct wiphy* priv_to_wiphy (struct qtnf_wmac*) ; 
 int /*<<< orphan*/  qtnf_bus_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_bus_unlock (int /*<<< orphan*/ ) ; 
 struct sk_buff* qtnf_cmd_alloc_new_cmdskb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int qtnf_cmd_send (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  qtnf_cmd_skb_put_tlv_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qtnf_cmd_skb_put_tlv_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qtnf_cmd_send_update_phy_params(struct qtnf_wmac *mac, u32 changed)
{
	struct wiphy *wiphy = priv_to_wiphy(mac);
	struct sk_buff *cmd_skb;
	int ret = 0;

	cmd_skb = qtnf_cmd_alloc_new_cmdskb(mac->macid, 0,
					    QLINK_CMD_PHY_PARAMS_SET,
					    sizeof(struct qlink_cmd));
	if (!cmd_skb)
		return -ENOMEM;

	qtnf_bus_lock(mac->bus);

	if (changed & WIPHY_PARAM_FRAG_THRESHOLD)
		qtnf_cmd_skb_put_tlv_u32(cmd_skb, QTN_TLV_ID_FRAG_THRESH,
					 wiphy->frag_threshold);
	if (changed & WIPHY_PARAM_RTS_THRESHOLD)
		qtnf_cmd_skb_put_tlv_u32(cmd_skb, QTN_TLV_ID_RTS_THRESH,
					 wiphy->rts_threshold);
	if (changed & WIPHY_PARAM_COVERAGE_CLASS)
		qtnf_cmd_skb_put_tlv_u8(cmd_skb, QTN_TLV_ID_COVERAGE_CLASS,
					wiphy->coverage_class);

	if (changed & WIPHY_PARAM_RETRY_LONG)
		qtnf_cmd_skb_put_tlv_u8(cmd_skb, QTN_TLV_ID_LRETRY_LIMIT,
					wiphy->retry_long);

	if (changed & WIPHY_PARAM_RETRY_SHORT)
		qtnf_cmd_skb_put_tlv_u8(cmd_skb, QTN_TLV_ID_SRETRY_LIMIT,
					wiphy->retry_short);

	ret = qtnf_cmd_send(mac->bus, cmd_skb);
	if (ret)
		goto out;

out:
	qtnf_bus_unlock(mac->bus);

	return ret;
}