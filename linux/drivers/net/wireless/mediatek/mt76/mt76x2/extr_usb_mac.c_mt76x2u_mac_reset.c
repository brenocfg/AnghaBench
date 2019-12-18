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
struct mt76x02_dev {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  MT_AUTO_RSP_CFG ; 
 int /*<<< orphan*/  MT_COEXCFG0 ; 
 int MT_COEXCFG0_COEX_EN ; 
 int /*<<< orphan*/  MT_EXT_CCA_CFG ; 
 int /*<<< orphan*/  MT_MAC_SYS_CTRL ; 
 int MT_MAC_SYS_CTRL_RESET_BBP ; 
 int MT_MAC_SYS_CTRL_RESET_CSR ; 
 int /*<<< orphan*/  MT_MAX_LEN_CFG ; 
 int /*<<< orphan*/  MT_PBF_RX_MAX_PCNT ; 
 int /*<<< orphan*/  MT_PBF_TX_MAX_PCNT ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_4 ; 
 int /*<<< orphan*/  MT_TX_LINK_CFG ; 
 int /*<<< orphan*/  MT_WMM_AIFSN ; 
 int /*<<< orphan*/  MT_WMM_CWMAX ; 
 int /*<<< orphan*/  MT_WMM_CWMIN ; 
 int /*<<< orphan*/  MT_WPDMA_GLO_CFG ; 
 scalar_t__ is_mt7612 (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_write_mac_initvals (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2u_mac_fixup_xtal (struct mt76x02_dev*) ; 

int mt76x2u_mac_reset(struct mt76x02_dev *dev)
{
	mt76_wr(dev, MT_WPDMA_GLO_CFG, BIT(4) | BIT(5));

	/* init pbf regs */
	mt76_wr(dev, MT_PBF_TX_MAX_PCNT, 0xefef3f1f);
	mt76_wr(dev, MT_PBF_RX_MAX_PCNT, 0xfebf);

	mt76_write_mac_initvals(dev);

	mt76_wr(dev, MT_TX_LINK_CFG, 0x1020);
	mt76_wr(dev, MT_AUTO_RSP_CFG, 0x13);
	mt76_wr(dev, MT_MAX_LEN_CFG, 0x2f00);

	mt76_wr(dev, MT_WMM_AIFSN, 0x2273);
	mt76_wr(dev, MT_WMM_CWMIN, 0x2344);
	mt76_wr(dev, MT_WMM_CWMAX, 0x34aa);

	mt76_clear(dev, MT_MAC_SYS_CTRL,
		   MT_MAC_SYS_CTRL_RESET_CSR |
		   MT_MAC_SYS_CTRL_RESET_BBP);

	if (is_mt7612(dev))
		mt76_clear(dev, MT_COEXCFG0, MT_COEXCFG0_COEX_EN);

	mt76_set(dev, MT_EXT_CCA_CFG, 0xf000);
	mt76_clear(dev, MT_TX_ALC_CFG_4, BIT(31));

	mt76x2u_mac_fixup_xtal(dev);

	return 0;
}