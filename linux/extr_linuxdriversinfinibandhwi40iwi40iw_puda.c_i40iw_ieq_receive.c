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
typedef  int /*<<< orphan*/  u32 ;
struct i40iw_sc_vsi {int /*<<< orphan*/  dev; struct i40iw_puda_rsrc* ieq; } ;
struct i40iw_sc_qp {int dummy; } ;
struct i40iw_puda_rsrc {int /*<<< orphan*/  rxq_invalid_cnt; int /*<<< orphan*/  rx_wqe_idx; int /*<<< orphan*/  stats_bad_qp_id; int /*<<< orphan*/  compl_rxwqe_idx; } ;
struct i40iw_puda_buf {int dummy; } ;

/* Variables and functions */
 struct i40iw_sc_qp* i40iw_ieq_get_qp (int /*<<< orphan*/ ,struct i40iw_puda_buf*) ; 
 int /*<<< orphan*/  i40iw_ieq_handle_exception (struct i40iw_puda_rsrc*,struct i40iw_sc_qp*,struct i40iw_puda_buf*) ; 
 int /*<<< orphan*/  i40iw_puda_ret_bufpool (struct i40iw_puda_rsrc*,struct i40iw_puda_buf*) ; 

__attribute__((used)) static void i40iw_ieq_receive(struct i40iw_sc_vsi *vsi,
			      struct i40iw_puda_buf *buf)
{
	struct i40iw_puda_rsrc *ieq = vsi->ieq;
	struct i40iw_sc_qp *qp = NULL;
	u32 wqe_idx = ieq->compl_rxwqe_idx;

	qp = i40iw_ieq_get_qp(vsi->dev, buf);
	if (!qp) {
		ieq->stats_bad_qp_id++;
		i40iw_puda_ret_bufpool(ieq, buf);
	} else {
		i40iw_ieq_handle_exception(ieq, qp, buf);
	}
	/*
	 * ieq->rx_wqe_idx is used by i40iw_puda_replenish_rq()
	 * on which wqe_idx to start replenish rq
	 */
	if (!ieq->rxq_invalid_cnt)
		ieq->rx_wqe_idx = wqe_idx;
	ieq->rxq_invalid_cnt++;
}