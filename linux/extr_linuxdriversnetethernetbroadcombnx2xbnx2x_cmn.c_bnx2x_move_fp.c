#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bnx2x_sp_objs {int index; struct bnx2x_sp_objs** txdata_ptr; struct bnx2x_agg_info* tpa_info; int /*<<< orphan*/  napi; } ;
struct bnx2x_fp_txdata {int dummy; } ;
struct bnx2x_fp_stats {int index; struct bnx2x_fp_stats** txdata_ptr; struct bnx2x_agg_info* tpa_info; int /*<<< orphan*/  napi; } ;
struct bnx2x_fastpath {int index; struct bnx2x_fastpath** txdata_ptr; struct bnx2x_agg_info* tpa_info; int /*<<< orphan*/  napi; } ;
struct bnx2x_agg_info {int dummy; } ;
struct bnx2x {int max_cos; struct bnx2x_sp_objs* bnx2x_txq; struct bnx2x_sp_objs* fp_stats; struct bnx2x_sp_objs* sp_objs; struct bnx2x_sp_objs* fp; } ;

/* Variables and functions */
 int BNX2X_NUM_ETH_QUEUES (struct bnx2x*) ; 
 int FCOE_IDX (struct bnx2x*) ; 
 int FCOE_TXQ_IDX_OFFSET ; 
 int /*<<< orphan*/  memcpy (struct bnx2x_sp_objs*,struct bnx2x_sp_objs*,int) ; 

__attribute__((used)) static inline void bnx2x_move_fp(struct bnx2x *bp, int from, int to)
{
	struct bnx2x_fastpath *from_fp = &bp->fp[from];
	struct bnx2x_fastpath *to_fp = &bp->fp[to];
	struct bnx2x_sp_objs *from_sp_objs = &bp->sp_objs[from];
	struct bnx2x_sp_objs *to_sp_objs = &bp->sp_objs[to];
	struct bnx2x_fp_stats *from_fp_stats = &bp->fp_stats[from];
	struct bnx2x_fp_stats *to_fp_stats = &bp->fp_stats[to];
	int old_max_eth_txqs, new_max_eth_txqs;
	int old_txdata_index = 0, new_txdata_index = 0;
	struct bnx2x_agg_info *old_tpa_info = to_fp->tpa_info;

	/* Copy the NAPI object as it has been already initialized */
	from_fp->napi = to_fp->napi;

	/* Move bnx2x_fastpath contents */
	memcpy(to_fp, from_fp, sizeof(*to_fp));
	to_fp->index = to;

	/* Retain the tpa_info of the original `to' version as we don't want
	 * 2 FPs to contain the same tpa_info pointer.
	 */
	to_fp->tpa_info = old_tpa_info;

	/* move sp_objs contents as well, as their indices match fp ones */
	memcpy(to_sp_objs, from_sp_objs, sizeof(*to_sp_objs));

	/* move fp_stats contents as well, as their indices match fp ones */
	memcpy(to_fp_stats, from_fp_stats, sizeof(*to_fp_stats));

	/* Update txdata pointers in fp and move txdata content accordingly:
	 * Each fp consumes 'max_cos' txdata structures, so the index should be
	 * decremented by max_cos x delta.
	 */

	old_max_eth_txqs = BNX2X_NUM_ETH_QUEUES(bp) * (bp)->max_cos;
	new_max_eth_txqs = (BNX2X_NUM_ETH_QUEUES(bp) - from + to) *
				(bp)->max_cos;
	if (from == FCOE_IDX(bp)) {
		old_txdata_index = old_max_eth_txqs + FCOE_TXQ_IDX_OFFSET;
		new_txdata_index = new_max_eth_txqs + FCOE_TXQ_IDX_OFFSET;
	}

	memcpy(&bp->bnx2x_txq[new_txdata_index],
	       &bp->bnx2x_txq[old_txdata_index],
	       sizeof(struct bnx2x_fp_txdata));
	to_fp->txdata_ptr[0] = &bp->bnx2x_txq[new_txdata_index];
}