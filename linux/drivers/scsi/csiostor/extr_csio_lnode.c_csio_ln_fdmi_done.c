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
struct csio_lnode {int dummy; } ;
struct TYPE_2__ {void* vaddr; } ;
struct csio_ioreq {TYPE_1__ dma_buf; int /*<<< orphan*/  wr_status; struct csio_lnode* lnode; } ;
struct csio_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ FC_FS_ACC ; 
 int /*<<< orphan*/  FW_SUCCESS ; 
 int /*<<< orphan*/  csio_ct_expl (void*) ; 
 int /*<<< orphan*/  csio_ct_reason (void*) ; 
 int /*<<< orphan*/  csio_ct_rsp (void*) ; 
 int /*<<< orphan*/  csio_ln_dbg (struct csio_lnode*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  n_fdmi_err ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
csio_ln_fdmi_done(struct csio_hw *hw, struct csio_ioreq *fdmi_req)
{
	void *cmd;
	struct csio_lnode *ln = fdmi_req->lnode;

	if (fdmi_req->wr_status != FW_SUCCESS) {
		csio_ln_dbg(ln, "WR error:%x in processing fdmi rpa cmd\n",
			    fdmi_req->wr_status);
		CSIO_INC_STATS(ln, n_fdmi_err);
	}

	cmd = fdmi_req->dma_buf.vaddr;
	if (ntohs(csio_ct_rsp(cmd)) != FC_FS_ACC) {
		csio_ln_dbg(ln, "fdmi rpa cmd rejected reason %x expl %x\n",
			    csio_ct_reason(cmd), csio_ct_expl(cmd));
	}
}