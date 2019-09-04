#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_5__ {size_t num_of_cos; TYPE_3__* cos_params; } ;
struct TYPE_4__ {TYPE_2__ ets; } ;
struct bnx2x {size_t* prio_to_cos; TYPE_1__ dcbx_port_params; } ;
struct TYPE_6__ {int pri_bitmask; } ;

/* Variables and functions */
 size_t BNX2X_MAX_PRIORITY ; 
 int /*<<< orphan*/  BNX2X_MSG_DCB ; 
 int /*<<< orphan*/  BNX2X_SP_RTNL_SETUP_TC ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int /*<<< orphan*/  bnx2x_schedule_sp_rtnl (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bnx2x_dcbx_update_tc_mapping(struct bnx2x *bp)
{
	u8 prio, cos;
	for (cos = 0; cos < bp->dcbx_port_params.ets.num_of_cos; cos++) {
		for (prio = 0; prio < BNX2X_MAX_PRIORITY; prio++) {
			if (bp->dcbx_port_params.ets.cos_params[cos].pri_bitmask
			    & (1 << prio)) {
				bp->prio_to_cos[prio] = cos;
				DP(BNX2X_MSG_DCB,
				   "tx_mapping %d --> %d\n", prio, cos);
			}
		}
	}

	/* setup tc must be called under rtnl lock, but we can't take it here
	 * as we are handling an attention on a work queue which must be
	 * flushed at some rtnl-locked contexts (e.g. if down)
	 */
	bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_SETUP_TC, 0);
}