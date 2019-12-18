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
typedef  int /*<<< orphan*/  u64 ;
struct niu_link_config {scalar_t__ loopback_mode; scalar_t__ active_speed; } ;
struct niu {int flags; struct niu_link_config link_config; } ;

/* Variables and functions */
 scalar_t__ LOOPBACK_MAC ; 
 int /*<<< orphan*/  MIF_CONFIG ; 
 int /*<<< orphan*/  MIF_CONFIG_ATCA_GE ; 
 int NIU_FLAGS_10G ; 
 int NIU_FLAGS_FIBER ; 
 int NIU_FLAGS_XCVR_SERDES ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  XMAC_CONFIG ; 
 int /*<<< orphan*/  XMAC_CONFIG_10G_XPCS_BYPASS ; 
 int /*<<< orphan*/  XMAC_CONFIG_1G_PCS_BYPASS ; 
 int /*<<< orphan*/  XMAC_CONFIG_LFS_DISABLE ; 
 int /*<<< orphan*/  XMAC_CONFIG_LOOPBACK ; 
 int /*<<< orphan*/  XMAC_CONFIG_MODE_GMII ; 
 int /*<<< orphan*/  XMAC_CONFIG_MODE_MASK ; 
 int /*<<< orphan*/  XMAC_CONFIG_MODE_MII ; 
 int /*<<< orphan*/  XMAC_CONFIG_MODE_XGMII ; 
 int /*<<< orphan*/  XMAC_CONFIG_SEL_CLK_25MHZ ; 
 int /*<<< orphan*/  XMAC_CONFIG_SEL_POR_CLK_SRC ; 
 int /*<<< orphan*/  XMAC_CONFIG_TX_OUTPUT_EN ; 
 int /*<<< orphan*/  nr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr64_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_init_xif_xmac(struct niu *np)
{
	struct niu_link_config *lp = &np->link_config;
	u64 val;

	if (np->flags & NIU_FLAGS_XCVR_SERDES) {
		val = nr64(MIF_CONFIG);
		val |= MIF_CONFIG_ATCA_GE;
		nw64(MIF_CONFIG, val);
	}

	val = nr64_mac(XMAC_CONFIG);
	val &= ~XMAC_CONFIG_SEL_POR_CLK_SRC;

	val |= XMAC_CONFIG_TX_OUTPUT_EN;

	if (lp->loopback_mode == LOOPBACK_MAC) {
		val &= ~XMAC_CONFIG_SEL_POR_CLK_SRC;
		val |= XMAC_CONFIG_LOOPBACK;
	} else {
		val &= ~XMAC_CONFIG_LOOPBACK;
	}

	if (np->flags & NIU_FLAGS_10G) {
		val &= ~XMAC_CONFIG_LFS_DISABLE;
	} else {
		val |= XMAC_CONFIG_LFS_DISABLE;
		if (!(np->flags & NIU_FLAGS_FIBER) &&
		    !(np->flags & NIU_FLAGS_XCVR_SERDES))
			val |= XMAC_CONFIG_1G_PCS_BYPASS;
		else
			val &= ~XMAC_CONFIG_1G_PCS_BYPASS;
	}

	val &= ~XMAC_CONFIG_10G_XPCS_BYPASS;

	if (lp->active_speed == SPEED_100)
		val |= XMAC_CONFIG_SEL_CLK_25MHZ;
	else
		val &= ~XMAC_CONFIG_SEL_CLK_25MHZ;

	nw64_mac(XMAC_CONFIG, val);

	val = nr64_mac(XMAC_CONFIG);
	val &= ~XMAC_CONFIG_MODE_MASK;
	if (np->flags & NIU_FLAGS_10G) {
		val |= XMAC_CONFIG_MODE_XGMII;
	} else {
		if (lp->active_speed == SPEED_1000)
			val |= XMAC_CONFIG_MODE_GMII;
		else
			val |= XMAC_CONFIG_MODE_MII;
	}

	nw64_mac(XMAC_CONFIG, val);
}