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
typedef  int uint8_t ;
struct fcoe_rdev_entry {int /*<<< orphan*/  vft_to_qos; int /*<<< orphan*/  rcv_fr_sz; int /*<<< orphan*/  wwpn; int /*<<< orphan*/  wwnn; int /*<<< orphan*/  enh_disc_to_tgt; int /*<<< orphan*/  event_cause; int /*<<< orphan*/  rd_xfer_rdy_to_rport_type; int /*<<< orphan*/ * r_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  sp_bb_data; } ;
struct TYPE_6__ {TYPE_2__* clsp; TYPE_1__ csp; } ;
struct csio_rnode {int nport_id; TYPE_3__ rn_sparm; int /*<<< orphan*/  role; int /*<<< orphan*/  fcp_flags; } ;
struct csio_lnode {int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_5__ {int /*<<< orphan*/  cp_class; } ;

/* Variables and functions */
 int CSIO_DID_MASK ; 
 int /*<<< orphan*/  CSIO_LNF_NPIVSUPP ; 
 int /*<<< orphan*/  CSIO_RNFR_FABRIC ; 
 int /*<<< orphan*/  CSIO_RNFR_INITIATOR ; 
 int /*<<< orphan*/  CSIO_RNFR_NPORT ; 
 int /*<<< orphan*/  CSIO_RNFR_NS ; 
 int /*<<< orphan*/  CSIO_RNFR_TARGET ; 
 int EINVAL ; 
#define  FAB_CTLR_VNPORT 133 
 int /*<<< orphan*/  FCP_SPPF_CONF_COMPL ; 
 int /*<<< orphan*/  FCP_SPPF_OVLY_ALLOW ; 
 int /*<<< orphan*/  FCP_SPPF_RETRY ; 
 int /*<<< orphan*/  FC_CPC_VALID ; 
 int FC_FID_DIR_SERV ; 
 int FC_FID_FLOGI ; 
#define  FDMI_VNPORT 132 
#define  FLOGI_VFPORT 131 
 int FW_RDEV_WR_CLASS_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_RDEV_WR_CONF_CMPL_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_RDEV_WR_INI_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_RDEV_WR_NPIV_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_RDEV_WR_RETRY_GET (int /*<<< orphan*/ ) ; 
 int FW_RDEV_WR_RPORT_TYPE_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_RDEV_WR_TASK_RETRY_ID_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_RDEV_WR_TGT_GET (int /*<<< orphan*/ ) ; 
#define  NS_VNPORT 130 
 int /*<<< orphan*/  PRLI_ACC_RCVD ; 
 int /*<<< orphan*/  PRLI_RCVD ; 
#define  REG_FC4_VNPORT 129 
#define  REG_VNPORT 128 
 int /*<<< orphan*/  csio_ln_err (struct csio_lnode*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  csio_rn_flowid (struct csio_rnode*) ; 
 int /*<<< orphan*/  csio_rn_wwnn (struct csio_rnode*) ; 
 int /*<<< orphan*/  csio_rn_wwpn (struct csio_rnode*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
csio_rn_verify_rparams(struct csio_lnode *ln, struct csio_rnode *rn,
			struct fcoe_rdev_entry *rdevp)
{
	uint8_t null[8];
	uint8_t rport_type;
	uint8_t fc_class;
	__be32 *did;

	did = (__be32 *) &rdevp->r_id[0];
	rport_type =
		FW_RDEV_WR_RPORT_TYPE_GET(rdevp->rd_xfer_rdy_to_rport_type);
	switch (rport_type) {
	case FLOGI_VFPORT:
		rn->role = CSIO_RNFR_FABRIC;
		if (((ntohl(*did) >> 8) & CSIO_DID_MASK) != FC_FID_FLOGI) {
			csio_ln_err(ln, "ssni:x%x invalid fabric portid\n",
				csio_rn_flowid(rn));
			return -EINVAL;
		}
		/* NPIV support */
		if (FW_RDEV_WR_NPIV_GET(rdevp->vft_to_qos))
			ln->flags |= CSIO_LNF_NPIVSUPP;

		break;

	case NS_VNPORT:
		rn->role = CSIO_RNFR_NS;
		if (((ntohl(*did) >> 8) & CSIO_DID_MASK) != FC_FID_DIR_SERV) {
			csio_ln_err(ln, "ssni:x%x invalid fabric portid\n",
				csio_rn_flowid(rn));
			return -EINVAL;
		}
		break;

	case REG_FC4_VNPORT:
	case REG_VNPORT:
		rn->role = CSIO_RNFR_NPORT;
		if (rdevp->event_cause == PRLI_ACC_RCVD ||
			rdevp->event_cause == PRLI_RCVD) {
			if (FW_RDEV_WR_TASK_RETRY_ID_GET(
							rdevp->enh_disc_to_tgt))
				rn->fcp_flags |= FCP_SPPF_OVLY_ALLOW;

			if (FW_RDEV_WR_RETRY_GET(rdevp->enh_disc_to_tgt))
				rn->fcp_flags |= FCP_SPPF_RETRY;

			if (FW_RDEV_WR_CONF_CMPL_GET(rdevp->enh_disc_to_tgt))
				rn->fcp_flags |= FCP_SPPF_CONF_COMPL;

			if (FW_RDEV_WR_TGT_GET(rdevp->enh_disc_to_tgt))
				rn->role |= CSIO_RNFR_TARGET;

			if (FW_RDEV_WR_INI_GET(rdevp->enh_disc_to_tgt))
				rn->role |= CSIO_RNFR_INITIATOR;
		}

		break;

	case FDMI_VNPORT:
	case FAB_CTLR_VNPORT:
		rn->role = 0;
		break;

	default:
		csio_ln_err(ln, "ssni:x%x invalid rport type recv x%x\n",
			csio_rn_flowid(rn), rport_type);
		return -EINVAL;
	}

	/* validate wwpn/wwnn for Name server/remote port */
	if (rport_type == REG_VNPORT || rport_type == NS_VNPORT) {
		memset(null, 0, 8);
		if (!memcmp(rdevp->wwnn, null, 8)) {
			csio_ln_err(ln,
				    "ssni:x%x invalid wwnn received from"
				    " rport did:x%x\n",
				    csio_rn_flowid(rn),
				    (ntohl(*did) & CSIO_DID_MASK));
			return -EINVAL;
		}

		if (!memcmp(rdevp->wwpn, null, 8)) {
			csio_ln_err(ln,
				    "ssni:x%x invalid wwpn received from"
				    " rport did:x%x\n",
				    csio_rn_flowid(rn),
				    (ntohl(*did) & CSIO_DID_MASK));
			return -EINVAL;
		}

	}

	/* Copy wwnn, wwpn and nport id */
	rn->nport_id = (ntohl(*did) >> 8) & CSIO_DID_MASK;
	memcpy(csio_rn_wwnn(rn), rdevp->wwnn, 8);
	memcpy(csio_rn_wwpn(rn), rdevp->wwpn, 8);
	rn->rn_sparm.csp.sp_bb_data = rdevp->rcv_fr_sz;
	fc_class = FW_RDEV_WR_CLASS_GET(rdevp->vft_to_qos);
	rn->rn_sparm.clsp[fc_class - 1].cp_class = htons(FC_CPC_VALID);

	return 0;
}