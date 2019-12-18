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
typedef  int u16 ;
struct TYPE_6__ {int hc_rate; int /*<<< orphan*/  flags; int /*<<< orphan*/  sb_cq_index; int /*<<< orphan*/  fw_sb_id; } ;
struct TYPE_5__ {int hc_rate; int /*<<< orphan*/  flags; int /*<<< orphan*/  sb_cq_index; int /*<<< orphan*/  fw_sb_id; } ;
struct bnx2x_queue_init_params {int /*<<< orphan*/ * cxts; TYPE_3__ rx; TYPE_2__ tx; } ;
struct TYPE_4__ {struct bnx2x_queue_init_params init; } ;
struct bnx2x_queue_state_params {TYPE_1__ params; struct bnx2x_queue_sp_obj* q_obj; } ;
struct bnx2x_queue_sp_obj {size_t max_cos; int /*<<< orphan*/  (* complete_cmd ) (struct bnx2x*,struct bnx2x_queue_sp_obj*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * cids; int /*<<< orphan*/  type; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  BNX2X_Q_CMD_INIT ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_HC ; 
 int /*<<< orphan*/  BNX2X_Q_FLG_HC_EN ; 
 int /*<<< orphan*/  BNX2X_Q_TYPE_HAS_RX ; 
 int /*<<< orphan*/  BNX2X_Q_TYPE_HAS_TX ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  bnx2x_set_ctx_validation (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_update_coalesce_sb_index (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  stub1 (struct bnx2x*,struct bnx2x_queue_sp_obj*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int bnx2x_q_init(struct bnx2x *bp,
			       struct bnx2x_queue_state_params *params)
{
	struct bnx2x_queue_sp_obj *o = params->q_obj;
	struct bnx2x_queue_init_params *init = &params->params.init;
	u16 hc_usec;
	u8 cos;

	/* Tx HC configuration */
	if (test_bit(BNX2X_Q_TYPE_HAS_TX, &o->type) &&
	    test_bit(BNX2X_Q_FLG_HC, &init->tx.flags)) {
		hc_usec = init->tx.hc_rate ? 1000000 / init->tx.hc_rate : 0;

		bnx2x_update_coalesce_sb_index(bp, init->tx.fw_sb_id,
			init->tx.sb_cq_index,
			!test_bit(BNX2X_Q_FLG_HC_EN, &init->tx.flags),
			hc_usec);
	}

	/* Rx HC configuration */
	if (test_bit(BNX2X_Q_TYPE_HAS_RX, &o->type) &&
	    test_bit(BNX2X_Q_FLG_HC, &init->rx.flags)) {
		hc_usec = init->rx.hc_rate ? 1000000 / init->rx.hc_rate : 0;

		bnx2x_update_coalesce_sb_index(bp, init->rx.fw_sb_id,
			init->rx.sb_cq_index,
			!test_bit(BNX2X_Q_FLG_HC_EN, &init->rx.flags),
			hc_usec);
	}

	/* Set CDU context validation values */
	for (cos = 0; cos < o->max_cos; cos++) {
		DP(BNX2X_MSG_SP, "setting context validation. cid %d, cos %d\n",
				 o->cids[cos], cos);
		DP(BNX2X_MSG_SP, "context pointer %p\n", init->cxts[cos]);
		bnx2x_set_ctx_validation(bp, init->cxts[cos], o->cids[cos]);
	}

	/* As no ramrod is sent, complete the command immediately  */
	o->complete_cmd(bp, o, BNX2X_Q_CMD_INIT);

	smp_mb();

	return 0;
}