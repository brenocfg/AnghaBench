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
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; } ;
struct TYPE_4__ {int /*<<< orphan*/  traffic_type; } ;
struct bnx2x_queue_setup_params {TYPE_2__ txq_params; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  hc_rate; int /*<<< orphan*/  sb_cq_index; } ;
struct bnx2x_queue_init_params {TYPE_1__ tx; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bnx2x_vfop_qctor_dump_tx(struct bnx2x *bp, struct bnx2x_virtf *vf,
			      struct bnx2x_queue_init_params *init_params,
			      struct bnx2x_queue_setup_params *setup_params,
			      u16 q_idx, u16 sb_idx)
{
	DP(BNX2X_MSG_IOV,
	   "VF[%d] Q_SETUP: txq[%d]-- vfsb=%d, sb-index=%d, hc-rate=%d, flags=0x%lx, traffic-type=%d",
	   vf->abs_vfid,
	   q_idx,
	   sb_idx,
	   init_params->tx.sb_cq_index,
	   init_params->tx.hc_rate,
	   setup_params->flags,
	   setup_params->txq_params.traffic_type);
}