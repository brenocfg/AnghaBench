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
struct bnx2x_virtf {int /*<<< orphan*/  abs_vfid; } ;
struct TYPE_2__ {int /*<<< orphan*/  func_id; } ;
struct bnx2x_vf_queue {int sp_initialized; int /*<<< orphan*/  cid; TYPE_1__ sp_obj; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  BNX2X_Q_TYPE_HAS_RX ; 
 int /*<<< orphan*/  BNX2X_Q_TYPE_HAS_TX ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_VF_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_init_queue_obj (struct bnx2x*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  bnx2x_vf_sp (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_vf_sp_map (struct bnx2x*,struct bnx2x_virtf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_data ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  vfq_cl_id (struct bnx2x_virtf*,struct bnx2x_vf_queue*) ; 

__attribute__((used)) static void bnx2x_vfq_init(struct bnx2x *bp, struct bnx2x_virtf *vf,
			   struct bnx2x_vf_queue *q)
{
	u8 cl_id = vfq_cl_id(vf, q);
	u8 func_id = FW_VF_HANDLE(vf->abs_vfid);
	unsigned long q_type = 0;

	set_bit(BNX2X_Q_TYPE_HAS_TX, &q_type);
	set_bit(BNX2X_Q_TYPE_HAS_RX, &q_type);

	/* Queue State object */
	bnx2x_init_queue_obj(bp, &q->sp_obj,
			     cl_id, &q->cid, 1, func_id,
			     bnx2x_vf_sp(bp, vf, q_data),
			     bnx2x_vf_sp_map(bp, vf, q_data),
			     q_type);

	/* sp indication is set only when vlan/mac/etc. are initialized */
	q->sp_initialized = false;

	DP(BNX2X_MSG_IOV,
	   "initialized vf %d's queue object. func id set to %d. cid set to 0x%x\n",
	   vf->abs_vfid, q->sp_obj.func_id, q->cid);
}