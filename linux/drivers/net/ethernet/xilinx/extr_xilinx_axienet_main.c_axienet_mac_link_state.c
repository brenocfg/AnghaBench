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
struct phylink_link_state {int duplex; scalar_t__ an_complete; int /*<<< orphan*/  pause; int /*<<< orphan*/  speed; int /*<<< orphan*/  interface; } ;
struct phylink_config {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct axienet_local {int /*<<< orphan*/  phy_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLO_PAUSE_RX ; 
 int /*<<< orphan*/  MLO_PAUSE_TX ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int XAE_EMMC_LINKSPD_100 ; 
 int XAE_EMMC_LINKSPD_1000 ; 
 int /*<<< orphan*/  XAE_EMMC_OFFSET ; 
 int XAE_FCC_FCRX_MASK ; 
 int XAE_FCC_FCTX_MASK ; 
 int /*<<< orphan*/  XAE_FCC_OFFSET ; 
 int axienet_ior (struct axienet_local*,int /*<<< orphan*/ ) ; 
 struct axienet_local* netdev_priv (struct net_device*) ; 
 struct net_device* to_net_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axienet_mac_link_state(struct phylink_config *config,
				  struct phylink_link_state *state)
{
	struct net_device *ndev = to_net_dev(config->dev);
	struct axienet_local *lp = netdev_priv(ndev);
	u32 emmc_reg, fcc_reg;

	state->interface = lp->phy_mode;

	emmc_reg = axienet_ior(lp, XAE_EMMC_OFFSET);
	if (emmc_reg & XAE_EMMC_LINKSPD_1000)
		state->speed = SPEED_1000;
	else if (emmc_reg & XAE_EMMC_LINKSPD_100)
		state->speed = SPEED_100;
	else
		state->speed = SPEED_10;

	state->pause = 0;
	fcc_reg = axienet_ior(lp, XAE_FCC_OFFSET);
	if (fcc_reg & XAE_FCC_FCTX_MASK)
		state->pause |= MLO_PAUSE_TX;
	if (fcc_reg & XAE_FCC_FCRX_MASK)
		state->pause |= MLO_PAUSE_RX;

	state->an_complete = 0;
	state->duplex = 1;

	return 1;
}