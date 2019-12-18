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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {void* len; void* type; } ;
struct qlink_channel {int /*<<< orphan*/  flags; int /*<<< orphan*/  dfs_state; int /*<<< orphan*/  beacon_found; int /*<<< orphan*/  max_antenna_gain; int /*<<< orphan*/  max_reg_power; int /*<<< orphan*/  max_power; int /*<<< orphan*/  band; void* hw_value; void* center_freq; } ;
struct qlink_tlv_channel {TYPE_1__ hdr; struct qlink_channel chan; } ;
struct ieee80211_channel {int center_freq; int hw_value; int /*<<< orphan*/  flags; int /*<<< orphan*/  dfs_state; int /*<<< orphan*/  beacon_found; int /*<<< orphan*/  max_antenna_gain; int /*<<< orphan*/  max_reg_power; int /*<<< orphan*/  max_power; int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int QTN_TLV_ID_CHANNEL ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlink_utils_band_cfg2q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlink_utils_chflags_cfg2q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlink_utils_dfs_state_cfg2q (int /*<<< orphan*/ ) ; 
 struct qlink_tlv_channel* skb_put_zero (struct sk_buff*,int) ; 

__attribute__((used)) static void qtnf_cmd_channel_tlv_add(struct sk_buff *cmd_skb,
				     const struct ieee80211_channel *sc)
{
	struct qlink_tlv_channel *tlv;
	struct qlink_channel *qch;

	tlv = skb_put_zero(cmd_skb, sizeof(*tlv));
	qch = &tlv->chan;
	tlv->hdr.type = cpu_to_le16(QTN_TLV_ID_CHANNEL);
	tlv->hdr.len = cpu_to_le16(sizeof(*qch));

	qch->center_freq = cpu_to_le16(sc->center_freq);
	qch->hw_value = cpu_to_le16(sc->hw_value);
	qch->band = qlink_utils_band_cfg2q(sc->band);
	qch->max_power = sc->max_power;
	qch->max_reg_power = sc->max_reg_power;
	qch->max_antenna_gain = sc->max_antenna_gain;
	qch->beacon_found = sc->beacon_found;
	qch->dfs_state = qlink_utils_dfs_state_cfg2q(sc->dfs_state);
	qch->flags = cpu_to_le32(qlink_utils_chflags_cfg2q(sc->flags));
}