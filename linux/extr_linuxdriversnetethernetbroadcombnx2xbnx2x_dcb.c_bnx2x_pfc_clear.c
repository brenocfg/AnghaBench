#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bnx2x_nig_brb_pfc_port_params {int pause_enable; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  feature_config_flags; } ;
struct bnx2x {int /*<<< orphan*/  link_vars; TYPE_1__ link_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEATURE_CONFIG_PFC_ENABLED ; 
 int /*<<< orphan*/  bnx2x_acquire_phy_lock (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_release_phy_lock (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_update_pfc (TYPE_1__*,int /*<<< orphan*/ *,struct bnx2x_nig_brb_pfc_port_params*) ; 

__attribute__((used)) static void bnx2x_pfc_clear(struct bnx2x *bp)
{
	struct bnx2x_nig_brb_pfc_port_params nig_params = {0};
	nig_params.pause_enable = 1;
	bnx2x_acquire_phy_lock(bp);
	bp->link_params.feature_config_flags &= ~FEATURE_CONFIG_PFC_ENABLED;
	bnx2x_update_pfc(&bp->link_params, &bp->link_vars, &nig_params);
	bnx2x_release_phy_lock(bp);
}