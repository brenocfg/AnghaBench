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
struct bcm_ns_usb3 {scalar_t__ dmp; } ;

/* Variables and functions */
 scalar_t__ BCMA_RESET_CTL ; 
 int /*<<< orphan*/  BCM_NS_USB3_LFPS_CMP ; 
 int /*<<< orphan*/  BCM_NS_USB3_LFPS_DEGLITCH ; 
 int /*<<< orphan*/  BCM_NS_USB3_PHY_BASE_ADDR_REG ; 
 int BCM_NS_USB3_PHY_PIPE_BLOCK ; 
 int BCM_NS_USB3_PHY_PLL30_BLOCK ; 
 int BCM_NS_USB3_PHY_TX_PMD_BLOCK ; 
 int /*<<< orphan*/  BCM_NS_USB3_PLLA_CONTROL0 ; 
 int /*<<< orphan*/  BCM_NS_USB3_PLLA_CONTROL1 ; 
 int /*<<< orphan*/  BCM_NS_USB3_PLL_CONTROL ; 
 int /*<<< orphan*/  BCM_NS_USB3_TX_PMD_CONTROL1 ; 
 int bcm_ns_usb3_mdio_phy_write (struct bcm_ns_usb3*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bcm_ns_usb3_phy_init_ns_bx(struct bcm_ns_usb3 *usb3)
{
	int err;

	/* USB3 PLL Block */
	err = bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_PHY_BASE_ADDR_REG,
					 BCM_NS_USB3_PHY_PLL30_BLOCK);
	if (err < 0)
		return err;

	/* Assert Ana_Pllseq start */
	bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_PLL_CONTROL, 0x1000);

	/* Assert CML Divider ratio to 26 */
	bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_PLLA_CONTROL0, 0x6400);

	/* Asserting PLL Reset */
	bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_PLLA_CONTROL1, 0xc000);

	/* Deaaserting PLL Reset */
	bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_PLLA_CONTROL1, 0x8000);

	/* Deasserting USB3 system reset */
	writel(0, usb3->dmp + BCMA_RESET_CTL);

	/* PLL frequency monitor enable */
	bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_PLL_CONTROL, 0x9000);

	/* PIPE Block */
	bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_PHY_BASE_ADDR_REG,
				   BCM_NS_USB3_PHY_PIPE_BLOCK);

	/* CMPMAX & CMPMINTH setting */
	bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_LFPS_CMP, 0xf30d);

	/* DEGLITCH MIN & MAX setting */
	bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_LFPS_DEGLITCH, 0x6302);

	/* TXPMD block */
	bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_PHY_BASE_ADDR_REG,
				   BCM_NS_USB3_PHY_TX_PMD_BLOCK);

	/* Enabling SSC */
	bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_TX_PMD_CONTROL1, 0x1003);

	return 0;
}