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
typedef  size_t u8 ;
struct bnx2x_txq_setup_params {int /*<<< orphan*/  traffic_type; scalar_t__ sb_cq_index; int /*<<< orphan*/  tss_leading_cl_id; int /*<<< orphan*/  fw_sb_id; int /*<<< orphan*/  dscr_map; } ;
struct bnx2x_fastpath {int /*<<< orphan*/  fw_sb_id; TYPE_1__** txdata_ptr; } ;
struct bnx2x {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_desc_mapping; } ;

/* Variables and functions */
 scalar_t__ HC_INDEX_ETH_FIRST_TX_CQ_CONS ; 
 scalar_t__ HC_SP_INDEX_ETH_FCOE_TX_CQ_CONS ; 
 scalar_t__ IS_FCOE_FP (struct bnx2x_fastpath*) ; 
 int /*<<< orphan*/  LLFC_TRAFFIC_TYPE_FCOE ; 
 int /*<<< orphan*/  LLFC_TRAFFIC_TYPE_NW ; 
 int /*<<< orphan*/  bnx2x_fp (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_id ; 

__attribute__((used)) static void bnx2x_pf_tx_q_prep(struct bnx2x *bp,
	struct bnx2x_fastpath *fp, struct bnx2x_txq_setup_params *txq_init,
	u8 cos)
{
	txq_init->dscr_map = fp->txdata_ptr[cos]->tx_desc_mapping;
	txq_init->sb_cq_index = HC_INDEX_ETH_FIRST_TX_CQ_CONS + cos;
	txq_init->traffic_type = LLFC_TRAFFIC_TYPE_NW;
	txq_init->fw_sb_id = fp->fw_sb_id;

	/*
	 * set the tss leading client id for TX classification ==
	 * leading RSS client id
	 */
	txq_init->tss_leading_cl_id = bnx2x_fp(bp, 0, cl_id);

	if (IS_FCOE_FP(fp)) {
		txq_init->sb_cq_index = HC_SP_INDEX_ETH_FCOE_TX_CQ_CONS;
		txq_init->traffic_type = LLFC_TRAFFIC_TYPE_FCOE;
	}
}