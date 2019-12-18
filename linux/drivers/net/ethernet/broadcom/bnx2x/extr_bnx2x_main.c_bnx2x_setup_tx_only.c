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
struct bnx2x_queue_state_params {TYPE_1__* q_obj; int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  spcl_id; } ;
struct bnx2x_queue_setup_tx_only_params {int cid_index; int /*<<< orphan*/  flags; TYPE_2__ gen_params; int /*<<< orphan*/  txq_params; } ;
struct bnx2x_fastpath {int dummy; } ;
struct bnx2x {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  cl_id; int /*<<< orphan*/ * cids; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_Q_CMD_SETUP_TX_ONLY ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t FIRST_TX_COS_INDEX ; 
 int /*<<< orphan*/  NETIF_MSG_IFUP ; 
 int /*<<< orphan*/  bnx2x_get_common_flags (struct bnx2x*,struct bnx2x_fastpath*,int) ; 
 int /*<<< orphan*/  bnx2x_pf_q_prep_general (struct bnx2x*,struct bnx2x_fastpath*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  bnx2x_pf_tx_q_prep (struct bnx2x*,struct bnx2x_fastpath*,int /*<<< orphan*/ *,int) ; 
 int bnx2x_queue_state_change (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int /*<<< orphan*/  memset (struct bnx2x_queue_setup_tx_only_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bnx2x_setup_tx_only(struct bnx2x *bp, struct bnx2x_fastpath *fp,
			struct bnx2x_queue_state_params *q_params,
			struct bnx2x_queue_setup_tx_only_params *tx_only_params,
			int tx_index, bool leading)
{
	memset(tx_only_params, 0, sizeof(*tx_only_params));

	/* Set the command */
	q_params->cmd = BNX2X_Q_CMD_SETUP_TX_ONLY;

	/* Set tx-only QUEUE flags: don't zero statistics */
	tx_only_params->flags = bnx2x_get_common_flags(bp, fp, false);

	/* choose the index of the cid to send the slow path on */
	tx_only_params->cid_index = tx_index;

	/* Set general TX_ONLY_SETUP parameters */
	bnx2x_pf_q_prep_general(bp, fp, &tx_only_params->gen_params, tx_index);

	/* Set Tx TX_ONLY_SETUP parameters */
	bnx2x_pf_tx_q_prep(bp, fp, &tx_only_params->txq_params, tx_index);

	DP(NETIF_MSG_IFUP,
	   "preparing to send tx-only ramrod for connection: cos %d, primary cid %d, cid %d, client id %d, sp-client id %d, flags %lx\n",
	   tx_index, q_params->q_obj->cids[FIRST_TX_COS_INDEX],
	   q_params->q_obj->cids[tx_index], q_params->q_obj->cl_id,
	   tx_only_params->gen_params.spcl_id, tx_only_params->flags);

	/* send the ramrod */
	return bnx2x_queue_state_change(bp, q_params);
}