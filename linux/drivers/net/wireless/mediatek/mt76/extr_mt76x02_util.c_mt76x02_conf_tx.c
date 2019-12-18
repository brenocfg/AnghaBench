#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct TYPE_6__ {TYPE_2__* q_tx; } ;
struct mt76x02_dev {TYPE_3__ mt76; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_queue_params {int txop; int aifs; scalar_t__ cw_max; scalar_t__ cw_min; } ;
struct ieee80211_hw {struct mt76x02_dev* priv; } ;
struct TYPE_5__ {TYPE_1__* q; } ;
struct TYPE_4__ {int hw_idx; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_EDCA_CFG_AC (int) ; 
 int /*<<< orphan*/  MT_EDCA_CFG_AIFSN ; 
 int /*<<< orphan*/  MT_EDCA_CFG_CWMAX ; 
 int /*<<< orphan*/  MT_EDCA_CFG_CWMIN ; 
 int /*<<< orphan*/  MT_EDCA_CFG_TXOP ; 
 int /*<<< orphan*/  MT_WMM_AIFSN ; 
 int MT_WMM_AIFSN_MASK ; 
 int MT_WMM_AIFSN_SHIFT (int) ; 
 int /*<<< orphan*/  MT_WMM_CWMAX ; 
 int MT_WMM_CWMAX_MASK ; 
 int MT_WMM_CWMAX_SHIFT (int) ; 
 int /*<<< orphan*/  MT_WMM_CWMIN ; 
 int MT_WMM_CWMIN_MASK ; 
 int MT_WMM_CWMIN_SHIFT (int) ; 
 int /*<<< orphan*/  MT_WMM_TXOP (int) ; 
 int MT_WMM_TXOP_MASK ; 
 int MT_WMM_TXOP_SHIFT (int) ; 
 int fls (scalar_t__) ; 
 int mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 

int mt76x02_conf_tx(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		    u16 queue, const struct ieee80211_tx_queue_params *params)
{
	struct mt76x02_dev *dev = hw->priv;
	u8 cw_min = 5, cw_max = 10, qid;
	u32 val;

	qid = dev->mt76.q_tx[queue].q->hw_idx;

	if (params->cw_min)
		cw_min = fls(params->cw_min);
	if (params->cw_max)
		cw_max = fls(params->cw_max);

	val = FIELD_PREP(MT_EDCA_CFG_TXOP, params->txop) |
	      FIELD_PREP(MT_EDCA_CFG_AIFSN, params->aifs) |
	      FIELD_PREP(MT_EDCA_CFG_CWMIN, cw_min) |
	      FIELD_PREP(MT_EDCA_CFG_CWMAX, cw_max);
	mt76_wr(dev, MT_EDCA_CFG_AC(qid), val);

	val = mt76_rr(dev, MT_WMM_TXOP(qid));
	val &= ~(MT_WMM_TXOP_MASK << MT_WMM_TXOP_SHIFT(qid));
	val |= params->txop << MT_WMM_TXOP_SHIFT(qid);
	mt76_wr(dev, MT_WMM_TXOP(qid), val);

	val = mt76_rr(dev, MT_WMM_AIFSN);
	val &= ~(MT_WMM_AIFSN_MASK << MT_WMM_AIFSN_SHIFT(qid));
	val |= params->aifs << MT_WMM_AIFSN_SHIFT(qid);
	mt76_wr(dev, MT_WMM_AIFSN, val);

	val = mt76_rr(dev, MT_WMM_CWMIN);
	val &= ~(MT_WMM_CWMIN_MASK << MT_WMM_CWMIN_SHIFT(qid));
	val |= cw_min << MT_WMM_CWMIN_SHIFT(qid);
	mt76_wr(dev, MT_WMM_CWMIN, val);

	val = mt76_rr(dev, MT_WMM_CWMAX);
	val &= ~(MT_WMM_CWMAX_MASK << MT_WMM_CWMAX_SHIFT(qid));
	val |= cw_max << MT_WMM_CWMAX_SHIFT(qid);
	mt76_wr(dev, MT_WMM_CWMAX, val);

	return 0;
}