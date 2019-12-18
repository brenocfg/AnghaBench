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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_IS_E3B0 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  bnx2x_ets_e3b0_nig_disabled (struct link_params const*,struct link_vars const*) ; 
 int /*<<< orphan*/  bnx2x_ets_e3b0_pbf_disabled (struct link_params const*) ; 

__attribute__((used)) static int bnx2x_ets_e3b0_disabled(const struct link_params *params,
				   const struct link_vars *vars)
{
	struct bnx2x *bp = params->bp;

	if (!CHIP_IS_E3B0(bp)) {
		DP(NETIF_MSG_LINK,
		   "bnx2x_ets_e3b0_disabled the chip isn't E3B0\n");
		return -EINVAL;
	}

	bnx2x_ets_e3b0_nig_disabled(params, vars);

	bnx2x_ets_e3b0_pbf_disabled(params);

	return 0;
}