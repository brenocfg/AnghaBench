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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mt7601u_dev {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_queue_params {int txop; int aifs; scalar_t__ cw_max; scalar_t__ cw_min; } ;
struct ieee80211_hw {struct mt7601u_dev* priv; } ;

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
 int /*<<< orphan*/  WARN_ON (int) ; 
 int fls (scalar_t__) ; 
 int mt76_rr (struct mt7601u_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7601u_dev*,int /*<<< orphan*/ ,int) ; 
 int q2hwq (int /*<<< orphan*/ ) ; 

int mt7601u_conf_tx(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		    u16 queue, const struct ieee80211_tx_queue_params *params)
{
	struct mt7601u_dev *dev = hw->priv;
	u8 cw_min = 5, cw_max = 10, hw_q = q2hwq(queue);
	u32 val;

	/* TODO: should we do funny things with the parameters?
	 *	 See what mt7601u_set_default_edca() used to do in init.c.
	 */

	if (params->cw_min)
		cw_min = fls(params->cw_min);
	if (params->cw_max)
		cw_max = fls(params->cw_max);

	WARN_ON(params->txop > 0xff);
	WARN_ON(params->aifs > 0xf);
	WARN_ON(cw_min > 0xf);
	WARN_ON(cw_max > 0xf);

	val = FIELD_PREP(MT_EDCA_CFG_AIFSN, params->aifs) |
	      FIELD_PREP(MT_EDCA_CFG_CWMIN, cw_min) |
	      FIELD_PREP(MT_EDCA_CFG_CWMAX, cw_max);
	/* TODO: based on user-controlled EnableTxBurst var vendor drv sets
	 *	 a really long txop on AC0 (see connect.c:2009) but only on
	 *	 connect? When not connected should be 0.
	 */
	if (!hw_q)
		val |= 0x60;
	else
		val |= FIELD_PREP(MT_EDCA_CFG_TXOP, params->txop);
	mt76_wr(dev, MT_EDCA_CFG_AC(hw_q), val);

	val = mt76_rr(dev, MT_WMM_TXOP(hw_q));
	val &= ~(MT_WMM_TXOP_MASK << MT_WMM_TXOP_SHIFT(hw_q));
	val |= params->txop << MT_WMM_TXOP_SHIFT(hw_q);
	mt76_wr(dev, MT_WMM_TXOP(hw_q), val);

	val = mt76_rr(dev, MT_WMM_AIFSN);
	val &= ~(MT_WMM_AIFSN_MASK << MT_WMM_AIFSN_SHIFT(hw_q));
	val |= params->aifs << MT_WMM_AIFSN_SHIFT(hw_q);
	mt76_wr(dev, MT_WMM_AIFSN, val);

	val = mt76_rr(dev, MT_WMM_CWMIN);
	val &= ~(MT_WMM_CWMIN_MASK << MT_WMM_CWMIN_SHIFT(hw_q));
	val |= cw_min << MT_WMM_CWMIN_SHIFT(hw_q);
	mt76_wr(dev, MT_WMM_CWMIN, val);

	val = mt76_rr(dev, MT_WMM_CWMAX);
	val &= ~(MT_WMM_CWMAX_MASK << MT_WMM_CWMAX_SHIFT(hw_q));
	val |= cw_max << MT_WMM_CWMAX_SHIFT(hw_q);
	mt76_wr(dev, MT_WMM_CWMAX, val);

	return 0;
}