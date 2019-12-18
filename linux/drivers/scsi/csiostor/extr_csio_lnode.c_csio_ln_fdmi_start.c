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
struct fc_fdmi_hba_identifier {int /*<<< orphan*/  id; } ;
struct csio_rnode {int dummy; } ;
struct csio_lnode {int flags; struct csio_ioreq* mgmt_req; } ;
struct TYPE_2__ {void* vaddr; } ;
struct csio_ioreq {TYPE_1__ dma_buf; struct csio_rnode* rnode; struct csio_lnode* lnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 int CSIO_LNF_FDMI_ENABLE ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  FCOE_CT ; 
 int FC_CT_HDR_LEN ; 
 int /*<<< orphan*/  FC_FDMI_DHBA ; 
 int /*<<< orphan*/  FC_FDMI_SUBTYPE ; 
 int /*<<< orphan*/  FC_FST_MGMT ; 
 scalar_t__ csio_ct_get_pld (void*) ; 
 int /*<<< orphan*/  csio_fill_ct_iu (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_is_rnode_ready (struct csio_rnode*) ; 
 int /*<<< orphan*/  csio_ln_dbg (struct csio_lnode*,char*) ; 
 int /*<<< orphan*/  csio_ln_fdmi_dhba_cbfn ; 
 scalar_t__ csio_ln_mgmt_submit_req (struct csio_ioreq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  csio_ln_wwpn (struct csio_lnode*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  n_fdmi_err ; 

int
csio_ln_fdmi_start(struct csio_lnode *ln, void *context)
{
	struct csio_ioreq *fdmi_req;
	struct csio_rnode *fdmi_rn = (struct csio_rnode *)context;
	void *cmd;
	struct fc_fdmi_hba_identifier *hbaid;
	uint32_t len;

	if (!(ln->flags & CSIO_LNF_FDMI_ENABLE))
		return -EPROTONOSUPPORT;

	if (!csio_is_rnode_ready(fdmi_rn))
		CSIO_INC_STATS(ln, n_fdmi_err);

	/* Send FDMI cmd to de-register any HBA attributes if registered
	 * before
	 */

	fdmi_req = ln->mgmt_req;
	fdmi_req->lnode = ln;
	fdmi_req->rnode = fdmi_rn;

	/* Prepare FDMI DHBA cmd */
	cmd = fdmi_req->dma_buf.vaddr;
	memset(cmd, 0, FC_CT_HDR_LEN);
	csio_fill_ct_iu(cmd, FC_FST_MGMT, FC_FDMI_SUBTYPE, FC_FDMI_DHBA);
	len = FC_CT_HDR_LEN;

	hbaid = (struct fc_fdmi_hba_identifier *)csio_ct_get_pld(cmd);
	memcpy(&hbaid->id, csio_ln_wwpn(ln), 8);
	len += sizeof(*hbaid);

	/* Submit FDMI request */
	if (csio_ln_mgmt_submit_req(fdmi_req, csio_ln_fdmi_dhba_cbfn,
					FCOE_CT, &fdmi_req->dma_buf, len)) {
		CSIO_INC_STATS(ln, n_fdmi_err);
		csio_ln_dbg(ln, "Failed to issue fdmi dhba req\n");
	}

	return 0;
}