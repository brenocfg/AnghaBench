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
typedef  int uint32_t ;
struct fc_fdmi_port_name {int /*<<< orphan*/  portname; } ;
struct csio_lnode {int dummy; } ;
struct TYPE_2__ {void* vaddr; } ;
struct csio_ioreq {TYPE_1__ dma_buf; int /*<<< orphan*/  rnode; int /*<<< orphan*/  wr_status; struct csio_lnode* lnode; } ;
struct csio_hw {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCOE_CT ; 
 int FC_CT_HDR_LEN ; 
 int /*<<< orphan*/  FC_FDMI_DPRT ; 
 int /*<<< orphan*/  FC_FDMI_SUBTYPE ; 
 int /*<<< orphan*/  FC_FST_MGMT ; 
 scalar_t__ FC_FS_ACC ; 
 int /*<<< orphan*/  FW_SUCCESS ; 
 int /*<<< orphan*/  csio_ct_expl (void*) ; 
 scalar_t__ csio_ct_get_pld (void*) ; 
 int /*<<< orphan*/  csio_ct_reason (void*) ; 
 int /*<<< orphan*/  csio_ct_rsp (void*) ; 
 int /*<<< orphan*/  csio_fill_ct_iu (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_is_rnode_ready (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_ln_dbg (struct csio_lnode*,char*,...) ; 
 int /*<<< orphan*/  csio_ln_fdmi_dprt_cbfn ; 
 scalar_t__ csio_ln_mgmt_submit_req (struct csio_ioreq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  csio_ln_wwpn (struct csio_lnode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  n_fdmi_err ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
csio_ln_fdmi_dhba_cbfn(struct csio_hw *hw, struct csio_ioreq *fdmi_req)
{
	struct csio_lnode *ln = fdmi_req->lnode;
	void *cmd;
	struct fc_fdmi_port_name *port_name;
	uint32_t len;

	if (fdmi_req->wr_status != FW_SUCCESS) {
		csio_ln_dbg(ln, "WR error:%x in processing fdmi dhba cmd\n",
			    fdmi_req->wr_status);
		CSIO_INC_STATS(ln, n_fdmi_err);
	}

	if (!csio_is_rnode_ready(fdmi_req->rnode)) {
		CSIO_INC_STATS(ln, n_fdmi_err);
		return;
	}
	cmd = fdmi_req->dma_buf.vaddr;
	if (ntohs(csio_ct_rsp(cmd)) != FC_FS_ACC) {
		csio_ln_dbg(ln, "fdmi dhba cmd rejected reason %x expl %x\n",
			    csio_ct_reason(cmd), csio_ct_expl(cmd));
	}

	/* Send FDMI cmd to de-register any Port attributes if registered
	 * before
	 */

	/* Prepare FDMI DPRT cmd */
	memset(cmd, 0, FC_CT_HDR_LEN);
	csio_fill_ct_iu(cmd, FC_FST_MGMT, FC_FDMI_SUBTYPE, FC_FDMI_DPRT);
	len = FC_CT_HDR_LEN;
	port_name = (struct fc_fdmi_port_name *)csio_ct_get_pld(cmd);
	memcpy(&port_name->portname, csio_ln_wwpn(ln), 8);
	len += sizeof(*port_name);

	/* Submit FDMI request */
	spin_lock_irq(&hw->lock);
	if (csio_ln_mgmt_submit_req(fdmi_req, csio_ln_fdmi_dprt_cbfn,
				FCOE_CT, &fdmi_req->dma_buf, len)) {
		CSIO_INC_STATS(ln, n_fdmi_err);
		csio_ln_dbg(ln, "Failed to issue fdmi dprt req\n");
	}
	spin_unlock_irq(&hw->lock);
}