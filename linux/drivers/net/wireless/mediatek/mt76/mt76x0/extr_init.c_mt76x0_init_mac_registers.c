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
 int /*<<< orphan*/  MT_EXT_CCA_CFG ; 
 int /*<<< orphan*/  MT_FCE_L2_STUFF ; 
 int MT_FCE_L2_STUFF_WR_MPDU_LEN_EN ; 
 int /*<<< orphan*/  MT_MAC_SYS_CTRL ; 
 int /*<<< orphan*/  MT_WMM_CTRL ; 
 int /*<<< orphan*/  RANDOM_WRITE (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common_mac_reg_table ; 
 int /*<<< orphan*/  mt76_clear (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_rmw (struct mt76x02_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76x0_mac_reg_table ; 

__attribute__((used)) static void mt76x0_init_mac_registers(struct mt76x02_dev *dev)
{
	RANDOM_WRITE(dev, common_mac_reg_table);

	/* Enable PBF and MAC clock SYS_CTRL[11:10] = 0x3 */
	RANDOM_WRITE(dev, mt76x0_mac_reg_table);

	/* Release BBP and MAC reset MAC_SYS_CTRL[1:0] = 0x0 */
	mt76_clear(dev, MT_MAC_SYS_CTRL, 0x3);

	/* Set 0x141C[15:12]=0xF */
	mt76_set(dev, MT_EXT_CCA_CFG, 0xf000);

	mt76_clear(dev, MT_FCE_L2_STUFF, MT_FCE_L2_STUFF_WR_MPDU_LEN_EN);

	/*
	 * tx_ring 9 is for mgmt frame
	 * tx_ring 8 is for in-band command frame.
	 * WMM_RG0_TXQMA: this register setting is for FCE to
	 *		  define the rule of tx_ring 9
	 * WMM_RG1_TXQMA: this register setting is for FCE to
	 *		  define the rule of tx_ring 8
	 */
	mt76_rmw(dev, MT_WMM_CTRL, 0x3ff, 0x201);
}