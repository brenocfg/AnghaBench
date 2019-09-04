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
typedef  int /*<<< orphan*/  u8 ;
struct bnx2x_virtf {int /*<<< orphan*/  filter_state; int /*<<< orphan*/  abs_vfid; } ;
struct bnx2x_vf_queue {int /*<<< orphan*/  cid; } ;
struct bnx2x_rx_mode_ramrod_params {unsigned long rx_accept_flags; unsigned long tx_accept_flags; int /*<<< orphan*/  rdata_mapping; int /*<<< orphan*/  rdata; int /*<<< orphan*/  ramrod_flags; int /*<<< orphan*/  state; int /*<<< orphan*/ * pstate; int /*<<< orphan*/  func_id; int /*<<< orphan*/ * rx_mode_obj; int /*<<< orphan*/  cl_id; int /*<<< orphan*/  cid; } ;
struct bnx2x {int /*<<< orphan*/  rx_mode_obj; } ;
struct TYPE_2__ {int /*<<< orphan*/  e2; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_FILTER_RX_MODE_PENDING ; 
 int /*<<< orphan*/  FW_VF_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAMROD_RX ; 
 int /*<<< orphan*/  RAMROD_TX ; 
 int /*<<< orphan*/  bnx2x_vf_sp (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vf_sp_map (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bnx2x_rx_mode_ramrod_params*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ rx_mode_rdata ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfq_cl_id (struct bnx2x_virtf*,struct bnx2x_vf_queue*) ; 
 struct bnx2x_vf_queue* vfq_get (struct bnx2x_virtf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_vf_prep_rx_mode(struct bnx2x *bp, u8 qid,
				  struct bnx2x_rx_mode_ramrod_params *ramrod,
				  struct bnx2x_virtf *vf,
				  unsigned long accept_flags)
{
	struct bnx2x_vf_queue *vfq = vfq_get(vf, qid);

	memset(ramrod, 0, sizeof(*ramrod));
	ramrod->cid = vfq->cid;
	ramrod->cl_id = vfq_cl_id(vf, vfq);
	ramrod->rx_mode_obj = &bp->rx_mode_obj;
	ramrod->func_id = FW_VF_HANDLE(vf->abs_vfid);
	ramrod->rx_accept_flags = accept_flags;
	ramrod->tx_accept_flags = accept_flags;
	ramrod->pstate = &vf->filter_state;
	ramrod->state = BNX2X_FILTER_RX_MODE_PENDING;

	set_bit(BNX2X_FILTER_RX_MODE_PENDING, &vf->filter_state);
	set_bit(RAMROD_RX, &ramrod->ramrod_flags);
	set_bit(RAMROD_TX, &ramrod->ramrod_flags);

	ramrod->rdata = bnx2x_vf_sp(bp, vf, rx_mode_rdata.e2);
	ramrod->rdata_mapping = bnx2x_vf_sp_map(bp, vf, rx_mode_rdata.e2);
}