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
typedef  int /*<<< orphan*/  uint8_t ;
struct fw_fcoe_vnp_cmd {scalar_t__ clsp_word_0_1; scalar_t__ cmn_srv_parms; int /*<<< orphan*/ * vnport_wwpn; int /*<<< orphan*/ * vnport_wwnn; int /*<<< orphan*/ * vnport_mac; int /*<<< orphan*/  alloc_to_len16; } ;
struct fc_els_cssp {int /*<<< orphan*/  cp_rdfs; int /*<<< orphan*/  cp_recip; int /*<<< orphan*/  cp_init; int /*<<< orphan*/  cp_class; } ;
struct fc_els_csp {int /*<<< orphan*/  sp_e_d_tov; int /*<<< orphan*/  sp_r_a_tov; int /*<<< orphan*/  sp_bb_data; int /*<<< orphan*/  sp_features; int /*<<< orphan*/  sp_bb_cred; int /*<<< orphan*/  sp_lo_ver; int /*<<< orphan*/  sp_hi_ver; } ;
struct csio_mb {scalar_t__ mb; scalar_t__ priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  sp_e_d_tov; int /*<<< orphan*/  sp_r_a_tov; int /*<<< orphan*/  sp_bb_data; int /*<<< orphan*/  sp_features; int /*<<< orphan*/  sp_bb_cred; int /*<<< orphan*/  sp_lo_ver; int /*<<< orphan*/  sp_hi_ver; } ;
struct TYPE_6__ {TYPE_2__* clsp; TYPE_1__ csp; } ;
struct csio_lnode {int nport_id; TYPE_3__ ln_sparm; int /*<<< orphan*/ * mac; } ;
struct csio_hw {int /*<<< orphan*/  mb_mempool; int /*<<< orphan*/  lock; } ;
typedef  enum fw_retval { ____Placeholder_fw_retval } fw_retval ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_5__ {int /*<<< orphan*/  cp_rdfs; int /*<<< orphan*/  cp_recip; int /*<<< orphan*/  cp_init; int /*<<< orphan*/  cp_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_LN_FC_ATTRIB_UPDATE ; 
 int FW_CMD_RETVAL_G (int) ; 
 int FW_SUCCESS ; 
 int /*<<< orphan*/  csio_err (struct csio_hw*,char*,int) ; 
 int /*<<< orphan*/ * csio_ln_wwnn (struct csio_lnode*) ; 
 int /*<<< orphan*/ * csio_ln_wwpn (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_lnode_async_event (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mempool_free (struct csio_mb*,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
csio_ln_vnp_read_cbfn(struct csio_hw *hw, struct csio_mb *mbp)
{
	struct csio_lnode *ln = ((struct csio_lnode *)mbp->priv);
	struct fw_fcoe_vnp_cmd *rsp = (struct fw_fcoe_vnp_cmd *)(mbp->mb);
	struct fc_els_csp *csp;
	struct fc_els_cssp *clsp;
	enum fw_retval retval;
	__be32 nport_id;

	retval = FW_CMD_RETVAL_G(ntohl(rsp->alloc_to_len16));
	if (retval != FW_SUCCESS) {
		csio_err(hw, "FCOE VNP read cmd returned error:0x%x\n", retval);
		mempool_free(mbp, hw->mb_mempool);
		return;
	}

	spin_lock_irq(&hw->lock);

	memcpy(ln->mac, rsp->vnport_mac, sizeof(ln->mac));
	memcpy(&nport_id, &rsp->vnport_mac[3], sizeof(uint8_t)*3);
	ln->nport_id = ntohl(nport_id);
	ln->nport_id = ln->nport_id >> 8;

	/* Update WWNs */
	/*
	 * This may look like a duplication of what csio_fcoe_enable_link()
	 * does, but is absolutely necessary if the vnpi changes between
	 * a FCOE LINK UP and FCOE LINK DOWN.
	 */
	memcpy(csio_ln_wwnn(ln), rsp->vnport_wwnn, 8);
	memcpy(csio_ln_wwpn(ln), rsp->vnport_wwpn, 8);

	/* Copy common sparam */
	csp = (struct fc_els_csp *)rsp->cmn_srv_parms;
	ln->ln_sparm.csp.sp_hi_ver = csp->sp_hi_ver;
	ln->ln_sparm.csp.sp_lo_ver = csp->sp_lo_ver;
	ln->ln_sparm.csp.sp_bb_cred = csp->sp_bb_cred;
	ln->ln_sparm.csp.sp_features = csp->sp_features;
	ln->ln_sparm.csp.sp_bb_data = csp->sp_bb_data;
	ln->ln_sparm.csp.sp_r_a_tov = csp->sp_r_a_tov;
	ln->ln_sparm.csp.sp_e_d_tov = csp->sp_e_d_tov;

	/* Copy word 0 & word 1 of class sparam */
	clsp = (struct fc_els_cssp *)rsp->clsp_word_0_1;
	ln->ln_sparm.clsp[2].cp_class = clsp->cp_class;
	ln->ln_sparm.clsp[2].cp_init = clsp->cp_init;
	ln->ln_sparm.clsp[2].cp_recip = clsp->cp_recip;
	ln->ln_sparm.clsp[2].cp_rdfs = clsp->cp_rdfs;

	spin_unlock_irq(&hw->lock);

	mempool_free(mbp, hw->mb_mempool);

	/* Send an event to update local attribs */
	csio_lnode_async_event(ln, CSIO_LN_FC_ATTRIB_UPDATE);
}