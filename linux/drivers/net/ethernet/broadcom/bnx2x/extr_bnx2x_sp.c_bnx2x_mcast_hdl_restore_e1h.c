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
typedef  int /*<<< orphan*/  u32 ;
struct bnx2x_mcast_ramrod_params {int dummy; } ;
struct bnx2x_mcast_obj {int dummy; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_57711_SET_MC_FILTER (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int bnx2x_mcast_get_next_bin (struct bnx2x_mcast_obj*,int) ; 

__attribute__((used)) static inline void bnx2x_mcast_hdl_restore_e1h(struct bnx2x *bp,
	struct bnx2x_mcast_obj *o, struct bnx2x_mcast_ramrod_params *p,
	u32 *mc_filter)
{
	int bit;

	for (bit = bnx2x_mcast_get_next_bin(o, 0);
	     bit >= 0;
	     bit = bnx2x_mcast_get_next_bin(o, bit + 1)) {
		BNX2X_57711_SET_MC_FILTER(mc_filter, bit);
		DP(BNX2X_MSG_SP, "About to set bin %d\n", bit);
	}
}