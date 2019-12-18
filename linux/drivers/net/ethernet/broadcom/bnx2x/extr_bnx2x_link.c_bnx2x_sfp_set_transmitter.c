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
typedef  int /*<<< orphan*/  u8 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E3 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  bnx2x_sfp_e1e2_set_transmitter (struct link_params*,struct bnx2x_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_sfp_e3_set_transmitter (struct link_params*,struct bnx2x_phy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_sfp_set_transmitter(struct link_params *params,
				      struct bnx2x_phy *phy,
				      u8 tx_en)
{
	struct bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "Setting SFP+ transmitter to %d\n", tx_en);
	if (CHIP_IS_E3(bp))
		bnx2x_sfp_e3_set_transmitter(params, phy, tx_en);
	else
		bnx2x_sfp_e1e2_set_transmitter(params, phy, tx_en);
}