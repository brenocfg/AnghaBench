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
struct mt7615_dev {int dummy; } ;

/* Variables and functions */
 int FIELD_PREP (int,int) ; 
 int MT7615_RATE_RETRY ; 
 int /*<<< orphan*/  MT_AGG_ACR0 ; 
 int /*<<< orphan*/  MT_AGG_ACR1 ; 
 int MT_AGG_ACR_BAR_RATE ; 
 int MT_AGG_ACR_CFEND_RATE ; 
 int MT_AGG_ACR_NO_BA_AR_RULE ; 
 int MT_AGG_ACR_PKT_TIME_EN ; 
 int /*<<< orphan*/  MT_AGG_ARCR ; 
 int MT_AGG_ARCR_RATE_DOWN_RATIO ; 
 int MT_AGG_ARCR_RATE_DOWN_RATIO_EN ; 
 int MT_AGG_ARCR_RATE_UP_EXTRA_TH ; 
 int MT_AGG_ARCR_RTS_RATE_THR ; 
 int /*<<< orphan*/  MT_AGG_ARDCR ; 
 int /*<<< orphan*/  MT_AGG_ARUCR ; 
 int MT_AGG_ARxCR_LIMIT (int) ; 
 int /*<<< orphan*/  MT_AGG_SCR ; 
 int MT_AGG_SCR_NLNAV_MID_PTEC_DIS ; 
 int /*<<< orphan*/  MT_CFG_CCR ; 
 int MT_CFG_CCR_MAC_D0_1X_GC_EN ; 
 int MT_CFG_CCR_MAC_D0_2X_GC_EN ; 
 int MT_CFG_CCR_MAC_D1_1X_GC_EN ; 
 int MT_CFG_CCR_MAC_D1_2X_GC_EN ; 
 int /*<<< orphan*/  MT_DMA_DCR0 ; 
 int MT_DMA_DCR0_MAX_RX_LEN ; 
 int MT_DMA_DCR0_RX_VEC_DROP ; 
 int /*<<< orphan*/  MT_TMAC_CTCR0 ; 
 int /*<<< orphan*/  MT_TMAC_CTCR0_INS_DDLMT_DENSITY ; 
 int MT_TMAC_CTCR0_INS_DDLMT_EN ; 
 int /*<<< orphan*/  MT_TMAC_CTCR0_INS_DDLMT_REFTIME ; 
 int MT_TMAC_CTCR0_INS_DDLMT_VHT_SMPDU_EN ; 
 int /*<<< orphan*/  MT_TMAC_TRCR0 ; 
 int /*<<< orphan*/  MT_TMAC_TRCR1 ; 
 int MT_TMAC_TRCR_CCA_SEL ; 
 int MT_TMAC_TRCR_SEC_CCA_SEL ; 
 int /*<<< orphan*/  mt7615_mac_set_scs (struct mt7615_dev*,int) ; 
 int /*<<< orphan*/  mt7615_mcu_init_mac (struct mt7615_dev*) ; 
 int /*<<< orphan*/  mt7615_mcu_set_rts_thresh (struct mt7615_dev*,int) ; 
 int mt76_rmw (struct mt7615_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt7615_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt7615_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7615_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mt7615_mac_init(struct mt7615_dev *dev)
{
	u32 val;

	/* enable band 0/1 clk */
	mt76_set(dev, MT_CFG_CCR,
		 MT_CFG_CCR_MAC_D0_1X_GC_EN | MT_CFG_CCR_MAC_D0_2X_GC_EN |
		 MT_CFG_CCR_MAC_D1_1X_GC_EN | MT_CFG_CCR_MAC_D1_2X_GC_EN);

	val = mt76_rmw(dev, MT_TMAC_TRCR0,
		       MT_TMAC_TRCR_CCA_SEL | MT_TMAC_TRCR_SEC_CCA_SEL,
		       FIELD_PREP(MT_TMAC_TRCR_CCA_SEL, 2) |
		       FIELD_PREP(MT_TMAC_TRCR_SEC_CCA_SEL, 0));
	mt76_wr(dev, MT_TMAC_TRCR1, val);

	val = MT_AGG_ACR_PKT_TIME_EN | MT_AGG_ACR_NO_BA_AR_RULE |
	      FIELD_PREP(MT_AGG_ACR_CFEND_RATE, 0x49) | /* 24M */
	      FIELD_PREP(MT_AGG_ACR_BAR_RATE, 0x4b); /* 6M */
	mt76_wr(dev, MT_AGG_ACR0, val);
	mt76_wr(dev, MT_AGG_ACR1, val);

	mt76_rmw_field(dev, MT_TMAC_CTCR0,
		       MT_TMAC_CTCR0_INS_DDLMT_REFTIME, 0x3f);
	mt76_rmw_field(dev, MT_TMAC_CTCR0,
		       MT_TMAC_CTCR0_INS_DDLMT_DENSITY, 0x3);
	mt76_rmw(dev, MT_TMAC_CTCR0,
		 MT_TMAC_CTCR0_INS_DDLMT_VHT_SMPDU_EN |
		 MT_TMAC_CTCR0_INS_DDLMT_EN,
		 MT_TMAC_CTCR0_INS_DDLMT_VHT_SMPDU_EN |
		 MT_TMAC_CTCR0_INS_DDLMT_EN);

	mt7615_mcu_set_rts_thresh(dev, 0x92b);
	mt7615_mac_set_scs(dev, false);

	mt76_rmw(dev, MT_AGG_SCR, MT_AGG_SCR_NLNAV_MID_PTEC_DIS,
		 MT_AGG_SCR_NLNAV_MID_PTEC_DIS);

	mt7615_mcu_init_mac(dev);

	mt76_wr(dev, MT_DMA_DCR0, MT_DMA_DCR0_RX_VEC_DROP |
		FIELD_PREP(MT_DMA_DCR0_MAX_RX_LEN, 3072));

	mt76_wr(dev, MT_AGG_ARUCR,
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(0), 7) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(1), 2) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(2), 2) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(3), 2) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(4), 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(5), 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(6), 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(7), 1));

	mt76_wr(dev, MT_AGG_ARDCR,
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(0), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(1), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(2), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(3), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(4), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(5), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(6), MT7615_RATE_RETRY - 1) |
		FIELD_PREP(MT_AGG_ARxCR_LIMIT(7), MT7615_RATE_RETRY - 1));

	mt76_wr(dev, MT_AGG_ARCR,
		(FIELD_PREP(MT_AGG_ARCR_RTS_RATE_THR, 2) |
		 MT_AGG_ARCR_RATE_DOWN_RATIO_EN |
		 FIELD_PREP(MT_AGG_ARCR_RATE_DOWN_RATIO, 1) |
		 FIELD_PREP(MT_AGG_ARCR_RATE_UP_EXTRA_TH, 4)));
}