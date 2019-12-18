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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * macaddr; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ETIMEDOUT ; 
 int FIELD_PREP (int,int) ; 
 int MT_CH_CCA_RC_EN ; 
 scalar_t__ MT_CH_TIME_CFG ; 
 int MT_CH_TIME_CFG_CH_TIMER_CLR ; 
 int MT_CH_TIME_CFG_EIFS_AS_BUSY ; 
 int MT_CH_TIME_CFG_NAV_AS_BUSY ; 
 int MT_CH_TIME_CFG_RX_AS_BUSY ; 
 int MT_CH_TIME_CFG_TIMER_EN ; 
 int MT_CH_TIME_CFG_TX_AS_BUSY ; 
 int /*<<< orphan*/  MT_COEXCFG0 ; 
 int MT_COEXCFG0_COEX_EN ; 
 int /*<<< orphan*/  MT_EXT_CCA_CFG ; 
 int /*<<< orphan*/  MT_FCE_L2_STUFF ; 
 int MT_FCE_L2_STUFF_WR_MPDU_LEN_EN ; 
 int /*<<< orphan*/  MT_MAC_SYS_CTRL ; 
 int MT_MAC_SYS_CTRL_RESET_BBP ; 
 int MT_MAC_SYS_CTRL_RESET_CSR ; 
 int MT_MAX_VIFS ; 
 scalar_t__ MT_MCU_CLOCK_CTL ; 
 scalar_t__ MT_RF_BYPASS_0 ; 
 scalar_t__ MT_RF_SETTING_0 ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_4 ; 
 scalar_t__ MT_TX_STAT_FIFO ; 
 int MT_VIF_WCID (int) ; 
 scalar_t__ MT_WCID_DROP_BASE ; 
 scalar_t__ MT_WCID_TX_RATE (int) ; 
 scalar_t__ MT_WPDMA_GLO_CFG ; 
 int MT_WPDMA_GLO_CFG_DMA_BURST_SIZE ; 
 int MT_WPDMA_GLO_CFG_RX_DMA_BUSY ; 
 int MT_WPDMA_GLO_CFG_RX_DMA_EN ; 
 int MT_WPDMA_GLO_CFG_TX_DMA_BUSY ; 
 int MT_WPDMA_GLO_CFG_TX_DMA_EN ; 
 scalar_t__ is_mt7612 (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int mt76_rr (struct mt76x02_dev*,scalar_t__) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,scalar_t__,int) ; 
 int /*<<< orphan*/  mt76_write_mac_initvals (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_mac_setaddr (struct mt76x02_dev*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mt76x02_mac_shared_key_setup (struct mt76x02_dev*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x02_mac_wcid_setup (struct mt76x02_dev*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76x02_set_tx_ackto (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_wait_for_mac (TYPE_1__*) ; 
 int /*<<< orphan*/  mt76x02e_init_beacon_config (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2_fixup_xtal (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2_mac_pbf_init (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int mt76x2_mac_reset(struct mt76x02_dev *dev, bool hard)
{
	const u8 *macaddr = dev->mt76.macaddr;
	u32 val;
	int i, k;

	if (!mt76x02_wait_for_mac(&dev->mt76))
		return -ETIMEDOUT;

	val = mt76_rr(dev, MT_WPDMA_GLO_CFG);

	val &= ~(MT_WPDMA_GLO_CFG_TX_DMA_EN |
		 MT_WPDMA_GLO_CFG_TX_DMA_BUSY |
		 MT_WPDMA_GLO_CFG_RX_DMA_EN |
		 MT_WPDMA_GLO_CFG_RX_DMA_BUSY |
		 MT_WPDMA_GLO_CFG_DMA_BURST_SIZE);
	val |= FIELD_PREP(MT_WPDMA_GLO_CFG_DMA_BURST_SIZE, 3);

	mt76_wr(dev, MT_WPDMA_GLO_CFG, val);

	mt76x2_mac_pbf_init(dev);
	mt76_write_mac_initvals(dev);
	mt76x2_fixup_xtal(dev);

	mt76_clear(dev, MT_MAC_SYS_CTRL,
		   MT_MAC_SYS_CTRL_RESET_CSR |
		   MT_MAC_SYS_CTRL_RESET_BBP);

	if (is_mt7612(dev))
		mt76_clear(dev, MT_COEXCFG0, MT_COEXCFG0_COEX_EN);

	mt76_set(dev, MT_EXT_CCA_CFG, 0x0000f000);
	mt76_clear(dev, MT_TX_ALC_CFG_4, BIT(31));

	mt76_wr(dev, MT_RF_BYPASS_0, 0x06000000);
	mt76_wr(dev, MT_RF_SETTING_0, 0x08800000);
	usleep_range(5000, 10000);
	mt76_wr(dev, MT_RF_BYPASS_0, 0x00000000);

	mt76_wr(dev, MT_MCU_CLOCK_CTL, 0x1401);
	mt76_clear(dev, MT_FCE_L2_STUFF, MT_FCE_L2_STUFF_WR_MPDU_LEN_EN);

	mt76x02_mac_setaddr(dev, macaddr);
	mt76x02e_init_beacon_config(dev);
	if (!hard)
		return 0;

	for (i = 0; i < 256 / 32; i++)
		mt76_wr(dev, MT_WCID_DROP_BASE + i * 4, 0);

	for (i = 0; i < 256; i++) {
		mt76x02_mac_wcid_setup(dev, i, 0, NULL);
		mt76_wr(dev, MT_WCID_TX_RATE(i), 0);
		mt76_wr(dev, MT_WCID_TX_RATE(i) + 4, 0);
	}

	for (i = 0; i < MT_MAX_VIFS; i++)
		mt76x02_mac_wcid_setup(dev, MT_VIF_WCID(i), i, NULL);

	for (i = 0; i < 16; i++)
		for (k = 0; k < 4; k++)
			mt76x02_mac_shared_key_setup(dev, i, k, NULL);

	for (i = 0; i < 16; i++)
		mt76_rr(dev, MT_TX_STAT_FIFO);

	mt76_wr(dev, MT_CH_TIME_CFG,
		MT_CH_TIME_CFG_TIMER_EN |
		MT_CH_TIME_CFG_TX_AS_BUSY |
		MT_CH_TIME_CFG_RX_AS_BUSY |
		MT_CH_TIME_CFG_NAV_AS_BUSY |
		MT_CH_TIME_CFG_EIFS_AS_BUSY |
		MT_CH_CCA_RC_EN |
		FIELD_PREP(MT_CH_TIME_CFG_CH_TIMER_CLR, 1));

	mt76x02_set_tx_ackto(dev);

	return 0;
}