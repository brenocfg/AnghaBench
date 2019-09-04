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
struct mii_phy {int mode; } ;

/* Variables and functions */
 int ACSR_PIN_PRIO_SELECT ; 
 int EPCR_GMII_MODE ; 
 int EPCR_MODE_MASK ; 
 int EPCR_RGMII_MODE ; 
 int EPCR_RTBI_MODE ; 
 int EPCR_TBI_MODE ; 
 int /*<<< orphan*/  MII_CIS8201_10BTCSR ; 
 int /*<<< orphan*/  MII_CIS8201_ACSR ; 
 int /*<<< orphan*/  MII_CIS8201_EPCR ; 
#define  PHY_INTERFACE_MODE_GMII 131 
#define  PHY_INTERFACE_MODE_RGMII 130 
#define  PHY_INTERFACE_MODE_RTBI 129 
#define  PHY_INTERFACE_MODE_TBI 128 
 int TENBTCSR_ECHO_DISABLE ; 
 int phy_read (struct mii_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct mii_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cis8201_init(struct mii_phy *phy)
{
	int epcr;

	epcr = phy_read(phy, MII_CIS8201_EPCR);
	if (epcr < 0)
		return epcr;

	epcr &= ~EPCR_MODE_MASK;

	switch (phy->mode) {
	case PHY_INTERFACE_MODE_TBI:
		epcr |= EPCR_TBI_MODE;
		break;
	case PHY_INTERFACE_MODE_RTBI:
		epcr |= EPCR_RTBI_MODE;
		break;
	case PHY_INTERFACE_MODE_GMII:
		epcr |= EPCR_GMII_MODE;
		break;
	case PHY_INTERFACE_MODE_RGMII:
	default:
		epcr |= EPCR_RGMII_MODE;
	}

	phy_write(phy, MII_CIS8201_EPCR, epcr);

	/* MII regs override strap pins */
	phy_write(phy, MII_CIS8201_ACSR,
		  phy_read(phy, MII_CIS8201_ACSR) | ACSR_PIN_PRIO_SELECT);

	/* Disable TX_EN -> CRS echo mode, otherwise 10/HDX doesn't work */
	phy_write(phy, MII_CIS8201_10BTCSR,
		  phy_read(phy, MII_CIS8201_10BTCSR) | TENBTCSR_ECHO_DISABLE);

	return 0;
}