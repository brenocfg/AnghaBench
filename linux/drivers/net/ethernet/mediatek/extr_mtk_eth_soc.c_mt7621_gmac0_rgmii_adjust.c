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
struct mtk_eth {int /*<<< orphan*/  ethsys; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ phy_interface_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETHSYS_CLKCFG0 ; 
 int /*<<< orphan*/  ETHSYS_SYSCFG ; 
 int ETHSYS_TRGMII_MT7621_DDR_PLL ; 
 int /*<<< orphan*/  ETHSYS_TRGMII_MT7621_MASK ; 
 scalar_t__ PHY_INTERFACE_MODE_TRGMII ; 
 int SYSCFG_DRAM_TYPE_DDR2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt7621_gmac0_rgmii_adjust(struct mtk_eth *eth,
				     phy_interface_t interface)
{
	u32 val;

	/* Check DDR memory type.
	 * Currently TRGMII mode with DDR2 memory is not supported.
	 */
	regmap_read(eth->ethsys, ETHSYS_SYSCFG, &val);
	if (interface == PHY_INTERFACE_MODE_TRGMII &&
	    val & SYSCFG_DRAM_TYPE_DDR2) {
		dev_err(eth->dev,
			"TRGMII mode with DDR2 memory is not supported!\n");
		return -EOPNOTSUPP;
	}

	val = (interface == PHY_INTERFACE_MODE_TRGMII) ?
		ETHSYS_TRGMII_MT7621_DDR_PLL : 0;

	regmap_update_bits(eth->ethsys, ETHSYS_CLKCFG0,
			   ETHSYS_TRGMII_MT7621_MASK, val);

	return 0;
}