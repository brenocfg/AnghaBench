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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  n_active; } ;
struct csio_mgmtm {TYPE_2__ stats; int /*<<< orphan*/  active_q; int /*<<< orphan*/  iq_idx; int /*<<< orphan*/  eq_idx; } ;
struct TYPE_3__ {int /*<<< orphan*/  sm_list; } ;
struct csio_ioreq {void (* io_cbfn ) (struct csio_hw*,struct csio_ioreq*) ;uintptr_t fw_handle; TYPE_1__ sm; int /*<<< orphan*/  iq_idx; int /*<<< orphan*/  eq_idx; int /*<<< orphan*/  lnode; } ;
struct csio_hw {int dummy; } ;
struct csio_dma_buf {int /*<<< orphan*/  len; } ;
typedef  enum fcoe_cmn_type { ____Placeholder_fcoe_cmn_type } fcoe_cmn_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct csio_mgmtm* csio_hw_to_mgmtm (struct csio_hw*) ; 
 int csio_ln_mgmt_submit_wr (struct csio_mgmtm*,struct csio_ioreq*,int,struct csio_dma_buf*,int /*<<< orphan*/ ) ; 
 struct csio_hw* csio_lnode_to_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
csio_ln_mgmt_submit_req(struct csio_ioreq *io_req,
		void (*io_cbfn) (struct csio_hw *, struct csio_ioreq *),
		enum fcoe_cmn_type req_type, struct csio_dma_buf *pld,
		uint32_t pld_len)
{
	struct csio_hw *hw = csio_lnode_to_hw(io_req->lnode);
	struct csio_mgmtm *mgmtm = csio_hw_to_mgmtm(hw);
	int rv;

	BUG_ON(pld_len > pld->len);

	io_req->io_cbfn = io_cbfn;	/* Upper layer callback handler */
	io_req->fw_handle = (uintptr_t) (io_req);
	io_req->eq_idx = mgmtm->eq_idx;
	io_req->iq_idx = mgmtm->iq_idx;

	rv = csio_ln_mgmt_submit_wr(mgmtm, io_req, req_type, pld, pld_len);
	if (rv == 0) {
		list_add_tail(&io_req->sm.sm_list, &mgmtm->active_q);
		mgmtm->stats.n_active++;
	}
	return rv;
}