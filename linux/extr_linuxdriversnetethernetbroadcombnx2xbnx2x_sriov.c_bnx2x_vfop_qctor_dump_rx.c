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
struct bnx2x_rxq_setup_params {int /*<<< orphan*/  cache_line_log; int /*<<< orphan*/  drop_flags; int /*<<< orphan*/  tpa_agg_sz; int /*<<< orphan*/  max_sges_pkt; int /*<<< orphan*/  sge_buf_sz; int /*<<< orphan*/  buf_sz; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtu; } ;
struct bnx2x_queue_setup_params {int /*<<< orphan*/  flags; TYPE_2__ gen_params; struct bnx2x_rxq_setup_params rxq_params; } ;
struct TYPE_3__ {int /*<<< orphan*/  hc_rate; int /*<<< orphan*/  sb_cq_index; } ;
struct bnx2x_queue_init_params {TYPE_1__ rx; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bnx2x_vfop_qctor_dump_rx(struct bnx2x *bp, struct bnx2x_virtf *vf,
			    struct bnx2x_queue_init_params *init_params,
			    struct bnx2x_queue_setup_params *setup_params,
			    u16 q_idx, u16 sb_idx)
{
	struct bnx2x_rxq_setup_params *rxq_params = &setup_params->rxq_params;

	DP(BNX2X_MSG_IOV, "VF[%d] Q_SETUP: rxq[%d]-- vfsb=%d, sb-index=%d, hc-rate=%d, mtu=%d, buf-size=%d\n"
	   "sge-size=%d, max_sge_pkt=%d, tpa-agg-size=%d, flags=0x%lx, drop-flags=0x%x, cache-log=%d\n",
	   vf->abs_vfid,
	   q_idx,
	   sb_idx,
	   init_params->rx.sb_cq_index,
	   init_params->rx.hc_rate,
	   setup_params->gen_params.mtu,
	   rxq_params->buf_sz,
	   rxq_params->sge_buf_sz,
	   rxq_params->max_sges_pkt,
	   rxq_params->tpa_agg_sz,
	   setup_params->flags,
	   rxq_params->drop_flags,
	   rxq_params->cache_line_log);
}