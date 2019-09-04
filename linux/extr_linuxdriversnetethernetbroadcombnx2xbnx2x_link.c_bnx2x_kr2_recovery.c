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
struct link_vars {int dummy; } ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  bnx2x_warpcore_enable_AN_KR2 (struct bnx2x_phy*,struct link_params*,struct link_vars*) ; 
 int /*<<< orphan*/  bnx2x_warpcore_restart_AN_KR (struct bnx2x_phy*,struct link_params*) ; 

__attribute__((used)) static void bnx2x_kr2_recovery(struct link_params *params,
			       struct link_vars *vars,
			       struct bnx2x_phy *phy)
{
	struct bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "KR2 recovery\n");
	bnx2x_warpcore_enable_AN_KR2(phy, params, vars);
	bnx2x_warpcore_restart_AN_KR(phy, params);
}