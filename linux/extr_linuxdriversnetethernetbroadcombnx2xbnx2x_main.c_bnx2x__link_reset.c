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
struct bnx2x {int /*<<< orphan*/  link_vars; int /*<<< orphan*/  link_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BP_NOMCP (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_acquire_phy_lock (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_lfa_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2x_release_phy_lock (struct bnx2x*) ; 

__attribute__((used)) static void bnx2x__link_reset(struct bnx2x *bp)
{
	if (!BP_NOMCP(bp)) {
		bnx2x_acquire_phy_lock(bp);
		bnx2x_lfa_reset(&bp->link_params, &bp->link_vars);
		bnx2x_release_phy_lock(bp);
	} else
		BNX2X_ERR("Bootcode is missing - can not reset link\n");
}