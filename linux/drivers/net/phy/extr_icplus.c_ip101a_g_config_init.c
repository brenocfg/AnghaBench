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
struct phy_device {struct ip101a_g_phy_priv* priv; } ;
struct ip101a_g_phy_priv {int sel_intr32; } ;

/* Variables and functions */
 int IP101A_G_APS_ON ; 
#define  IP101GR_SEL_INTR32_INTR 129 
#define  IP101GR_SEL_INTR32_RXER 128 
 int /*<<< orphan*/  IP101G_DIGITAL_IO_SPEC_CTRL ; 
 int /*<<< orphan*/  IP101G_DIGITAL_IO_SPEC_CTRL_SEL_INTR32 ; 
 int /*<<< orphan*/  IP10XX_SPEC_CTRL_STATUS ; 
 int ip1xx_reset (struct phy_device*) ; 
 int phy_modify (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ip101a_g_config_init(struct phy_device *phydev)
{
	struct ip101a_g_phy_priv *priv = phydev->priv;
	int err, c;

	c = ip1xx_reset(phydev);
	if (c < 0)
		return c;

	/* configure the RXER/INTR_32 pin of the 32-pin IP101GR if needed: */
	switch (priv->sel_intr32) {
	case IP101GR_SEL_INTR32_RXER:
		err = phy_modify(phydev, IP101G_DIGITAL_IO_SPEC_CTRL,
				 IP101G_DIGITAL_IO_SPEC_CTRL_SEL_INTR32, 0);
		if (err < 0)
			return err;
		break;

	case IP101GR_SEL_INTR32_INTR:
		err = phy_modify(phydev, IP101G_DIGITAL_IO_SPEC_CTRL,
				 IP101G_DIGITAL_IO_SPEC_CTRL_SEL_INTR32,
				 IP101G_DIGITAL_IO_SPEC_CTRL_SEL_INTR32);
		if (err < 0)
			return err;
		break;

	default:
		/* Don't touch IP101G_DIGITAL_IO_SPEC_CTRL because it's not
		 * documented on IP101A and it's not clear whether this would
		 * cause problems.
		 * For the 32-pin IP101GR we simply keep the SEL_INTR32
		 * configuration as set by the bootloader when not configured
		 * to one of the special functions.
		 */
		break;
	}

	/* Enable Auto Power Saving mode */
	c = phy_read(phydev, IP10XX_SPEC_CTRL_STATUS);
	c |= IP101A_G_APS_ON;

	return phy_write(phydev, IP10XX_SPEC_CTRL_STATUS, c);
}