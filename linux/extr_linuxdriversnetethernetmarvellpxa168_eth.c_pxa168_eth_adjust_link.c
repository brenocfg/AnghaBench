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
struct pxa168_eth_private {int dummy; } ;
struct phy_device {scalar_t__ interface; scalar_t__ speed; int /*<<< orphan*/  pause; scalar_t__ duplex; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 int PCR_DUPLEX_FULL ; 
 int PCXR_FLOWCTL_DIS ; 
 int PCXR_RMII_EN ; 
 int PCXR_SPEED_100 ; 
 scalar_t__ PHY_INTERFACE_MODE_RMII ; 
 int /*<<< orphan*/  PORT_CONFIG ; 
 int /*<<< orphan*/  PORT_CONFIG_EXT ; 
 scalar_t__ SPEED_100 ; 
 struct pxa168_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 
 int rdl (struct pxa168_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrl (struct pxa168_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pxa168_eth_adjust_link(struct net_device *dev)
{
	struct pxa168_eth_private *pep = netdev_priv(dev);
	struct phy_device *phy = dev->phydev;
	u32 cfg, cfg_o = rdl(pep, PORT_CONFIG);
	u32 cfgext, cfgext_o = rdl(pep, PORT_CONFIG_EXT);

	cfg = cfg_o & ~PCR_DUPLEX_FULL;
	cfgext = cfgext_o & ~(PCXR_SPEED_100 | PCXR_FLOWCTL_DIS | PCXR_RMII_EN);

	if (phy->interface == PHY_INTERFACE_MODE_RMII)
		cfgext |= PCXR_RMII_EN;
	if (phy->speed == SPEED_100)
		cfgext |= PCXR_SPEED_100;
	if (phy->duplex)
		cfg |= PCR_DUPLEX_FULL;
	if (!phy->pause)
		cfgext |= PCXR_FLOWCTL_DIS;

	/* Bail out if there has nothing changed */
	if (cfg == cfg_o && cfgext == cfgext_o)
		return;

	wrl(pep, PORT_CONFIG, cfg);
	wrl(pep, PORT_CONFIG_EXT, cfgext);

	phy_print_status(phy);
}