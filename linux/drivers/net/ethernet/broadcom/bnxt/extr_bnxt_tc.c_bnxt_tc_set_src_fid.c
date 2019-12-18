#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int flags; } ;
struct bnxt_tc_flow {int /*<<< orphan*/  src_fid; TYPE_1__ actions; } ;
struct TYPE_4__ {int /*<<< orphan*/  fw_fid; } ;
struct bnxt {TYPE_2__ pf; } ;

/* Variables and functions */
 int BNXT_TC_ACTION_FLAG_TUNNEL_DECAP ; 

__attribute__((used)) static void bnxt_tc_set_src_fid(struct bnxt *bp, struct bnxt_tc_flow *flow,
				u16 src_fid)
{
	if (flow->actions.flags & BNXT_TC_ACTION_FLAG_TUNNEL_DECAP)
		flow->src_fid = bp->pf.fw_fid;
	else
		flow->src_fid = src_fid;
}