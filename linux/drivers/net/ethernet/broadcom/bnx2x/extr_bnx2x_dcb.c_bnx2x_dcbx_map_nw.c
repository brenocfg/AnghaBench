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
typedef  int u32 ;
struct bnx2x_dcbx_cos_params {int pri_bitmask; } ;
struct TYPE_5__ {struct bnx2x_dcbx_cos_params* cos_params; } ;
struct TYPE_4__ {int* traffic_type_priority; } ;
struct TYPE_6__ {TYPE_2__ ets; TYPE_1__ app; } ;
struct bnx2x {TYPE_3__ dcbx_port_params; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bnx2x_dcbx_cos_params*) ; 
 int /*<<< orphan*/  BNX2X_MSG_DCB ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int) ; 
 int LLFC_DRIVER_TRAFFIC_TYPE_MAX ; 
 size_t LLFC_TRAFFIC_TYPE_NW ; 
 int MAX_PFC_PRIORITIES ; 

__attribute__((used)) static void bnx2x_dcbx_map_nw(struct bnx2x *bp)
{
	int i;
	u32 unmapped = (1 << MAX_PFC_PRIORITIES) - 1; /* all ones */
	u32 *ttp = bp->dcbx_port_params.app.traffic_type_priority;
	u32 nw_prio = 1 << ttp[LLFC_TRAFFIC_TYPE_NW];
	struct bnx2x_dcbx_cos_params *cos_params =
			bp->dcbx_port_params.ets.cos_params;

	/* get unmapped priorities by clearing mapped bits */
	for (i = 0; i < LLFC_DRIVER_TRAFFIC_TYPE_MAX; i++)
		unmapped &= ~(1 << ttp[i]);

	/* find cos for nw prio and extend it with unmapped */
	for (i = 0; i < ARRAY_SIZE(bp->dcbx_port_params.ets.cos_params); i++) {
		if (cos_params[i].pri_bitmask & nw_prio) {
			/* extend the bitmask with unmapped */
			DP(BNX2X_MSG_DCB,
			   "cos %d extended with 0x%08x\n", i, unmapped);
			cos_params[i].pri_bitmask |= unmapped;
			break;
		}
	}
}