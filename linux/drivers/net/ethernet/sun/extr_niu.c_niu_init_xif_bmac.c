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
typedef  int u64 ;
struct niu_link_config {scalar_t__ loopback_mode; scalar_t__ active_speed; } ;
struct niu {int flags; struct niu_link_config link_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMAC_XIF_CONFIG ; 
 int BMAC_XIF_CONFIG_25MHZ_CLOCK ; 
 int BMAC_XIF_CONFIG_GMII_MODE ; 
 int BMAC_XIF_CONFIG_LED_POLARITY ; 
 int BMAC_XIF_CONFIG_LINK_LED ; 
 int BMAC_XIF_CONFIG_MII_LOOPBACK ; 
 int BMAC_XIF_CONFIG_TX_OUTPUT_EN ; 
 scalar_t__ LOOPBACK_MAC ; 
 int NIU_FLAGS_10G ; 
 int NIU_FLAGS_FIBER ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  nw64_mac (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void niu_init_xif_bmac(struct niu *np)
{
	struct niu_link_config *lp = &np->link_config;
	u64 val;

	val = BMAC_XIF_CONFIG_TX_OUTPUT_EN;

	if (lp->loopback_mode == LOOPBACK_MAC)
		val |= BMAC_XIF_CONFIG_MII_LOOPBACK;
	else
		val &= ~BMAC_XIF_CONFIG_MII_LOOPBACK;

	if (lp->active_speed == SPEED_1000)
		val |= BMAC_XIF_CONFIG_GMII_MODE;
	else
		val &= ~BMAC_XIF_CONFIG_GMII_MODE;

	val &= ~(BMAC_XIF_CONFIG_LINK_LED |
		 BMAC_XIF_CONFIG_LED_POLARITY);

	if (!(np->flags & NIU_FLAGS_10G) &&
	    !(np->flags & NIU_FLAGS_FIBER) &&
	    lp->active_speed == SPEED_100)
		val |= BMAC_XIF_CONFIG_25MHZ_CLOCK;
	else
		val &= ~BMAC_XIF_CONFIG_25MHZ_CLOCK;

	nw64_mac(BMAC_XIF_CONFIG, val);
}