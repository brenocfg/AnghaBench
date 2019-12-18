#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct lpfc_vport {int fc_flag; scalar_t__ num_disc_nodes; scalar_t__ port_state; int /*<<< orphan*/  fc_rscn_id_cnt; } ;
struct TYPE_11__ {scalar_t__ CmdRsp; } ;
struct TYPE_12__ {TYPE_4__ bits; } ;
struct TYPE_9__ {int* fbits; } ;
struct TYPE_8__ {int PortId; } ;
struct TYPE_10__ {TYPE_2__ gff_acc; TYPE_1__ gff; } ;
struct lpfc_sli_ct_request {TYPE_5__ CommandResponse; TYPE_3__ un; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_flag; } ;
struct TYPE_13__ {int* ulpWord; } ;
struct TYPE_14__ {TYPE_6__ un; int /*<<< orphan*/  ulpStatus; } ;
struct lpfc_iocbq {scalar_t__ retry; scalar_t__ context2; scalar_t__ context1; TYPE_7__ iocb; struct lpfc_vport* vport; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
typedef  TYPE_7__ IOCB_t ;

/* Variables and functions */
 int FC4_FEATURE_INIT ; 
 int FC4_FEATURE_TARGET ; 
 size_t FCP_TYPE_FEATURE_OFFSET ; 
 int FC_RSCN_MODE ; 
#define  IOERR_LINK_DOWN 131 
#define  IOERR_NO_RESOURCES 130 
 int IOERR_PARAM_MASK ; 
#define  IOERR_SLI_ABORTED 129 
#define  IOERR_SLI_DOWN 128 
 int /*<<< orphan*/  IOSTAT_LOCAL_REJECT ; 
 int /*<<< orphan*/  IOSTAT_SUCCESS ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 scalar_t__ LPFC_DISC_AUTH ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_CT ; 
 scalar_t__ LPFC_MAX_NS_RETRY ; 
 scalar_t__ NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  SLI_CTNS_GFF_ID ; 
 int /*<<< orphan*/  SLI_CT_RESPONSE_FS_ACC ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int) ; 
 int /*<<< orphan*/  lpfc_ct_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lpfc_disc_start (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_els_flush_rscn (struct lpfc_vport*) ; 
 int lpfc_ns_cmd (struct lpfc_vport*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,...) ; 
 struct lpfc_nodelist* lpfc_setup_disc_node (struct lpfc_vport*,int) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_cmpl_ct_cmd_gff_id(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
			struct lpfc_iocbq *rspiocb)
{
	struct lpfc_vport *vport = cmdiocb->vport;
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	IOCB_t *irsp = &rspiocb->iocb;
	struct lpfc_dmabuf *inp = (struct lpfc_dmabuf *) cmdiocb->context1;
	struct lpfc_dmabuf *outp = (struct lpfc_dmabuf *) cmdiocb->context2;
	struct lpfc_sli_ct_request *CTrsp;
	int did, rc, retry;
	uint8_t fbits;
	struct lpfc_nodelist *ndlp;

	did = ((struct lpfc_sli_ct_request *) inp->virt)->un.gff.PortId;
	did = be32_to_cpu(did);

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_CT,
		"GFF_ID cmpl:     status:x%x/x%x did:x%x",
		irsp->ulpStatus, irsp->un.ulpWord[4], did);

	if (irsp->ulpStatus == IOSTAT_SUCCESS) {
		/* Good status, continue checking */
		CTrsp = (struct lpfc_sli_ct_request *) outp->virt;
		fbits = CTrsp->un.gff_acc.fbits[FCP_TYPE_FEATURE_OFFSET];

		lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
				 "6431 Process GFF_ID rsp for %08x "
				 "fbits %02x %s %s\n",
				 did, fbits,
				 (fbits & FC4_FEATURE_INIT) ? "Initiator" : " ",
				 (fbits & FC4_FEATURE_TARGET) ? "Target" : " ");

		if (CTrsp->CommandResponse.bits.CmdRsp ==
		    be16_to_cpu(SLI_CT_RESPONSE_FS_ACC)) {
			if ((fbits & FC4_FEATURE_INIT) &&
			    !(fbits & FC4_FEATURE_TARGET)) {
				lpfc_printf_vlog(vport, KERN_INFO,
						 LOG_DISCOVERY,
						 "0270 Skip x%x GFF "
						 "NameServer Rsp Data: (init) "
						 "x%x x%x\n", did, fbits,
						 vport->fc_rscn_id_cnt);
				goto out;
			}
		}
	}
	else {
		/* Check for retry */
		if (cmdiocb->retry < LPFC_MAX_NS_RETRY) {
			retry = 1;
			if (irsp->ulpStatus == IOSTAT_LOCAL_REJECT) {
				switch ((irsp->un.ulpWord[4] &
					IOERR_PARAM_MASK)) {

				case IOERR_NO_RESOURCES:
					/* We don't increment the retry
					 * count for this case.
					 */
					break;
				case IOERR_LINK_DOWN:
				case IOERR_SLI_ABORTED:
				case IOERR_SLI_DOWN:
					retry = 0;
					break;
				default:
					cmdiocb->retry++;
				}
			}
			else
				cmdiocb->retry++;

			if (retry) {
				/* CT command is being retried */
				rc = lpfc_ns_cmd(vport, SLI_CTNS_GFF_ID,
					 cmdiocb->retry, did);
				if (rc == 0) {
					/* success */
					lpfc_ct_free_iocb(phba, cmdiocb);
					return;
				}
			}
		}
		lpfc_printf_vlog(vport, KERN_ERR, LOG_DISCOVERY,
				 "0267 NameServer GFF Rsp "
				 "x%x Error (%d %d) Data: x%x x%x\n",
				 did, irsp->ulpStatus, irsp->un.ulpWord[4],
				 vport->fc_flag, vport->fc_rscn_id_cnt);
	}

	/* This is a target port, unregistered port, or the GFF_ID failed */
	ndlp = lpfc_setup_disc_node(vport, did);
	if (ndlp && NLP_CHK_NODE_ACT(ndlp)) {
		lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
				 "0242 Process x%x GFF "
				 "NameServer Rsp Data: x%x x%x x%x\n",
				 did, ndlp->nlp_flag, vport->fc_flag,
				 vport->fc_rscn_id_cnt);
	} else {
		lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
				 "0243 Skip x%x GFF "
				 "NameServer Rsp Data: x%x x%x\n", did,
				 vport->fc_flag, vport->fc_rscn_id_cnt);
	}
out:
	/* Link up / RSCN discovery */
	if (vport->num_disc_nodes)
		vport->num_disc_nodes--;
	if (vport->num_disc_nodes == 0) {
		/*
		 * The driver has cycled through all Nports in the RSCN payload.
		 * Complete the handling by cleaning up and marking the
		 * current driver state.
		 */
		if (vport->port_state >= LPFC_DISC_AUTH) {
			if (vport->fc_flag & FC_RSCN_MODE) {
				lpfc_els_flush_rscn(vport);
				spin_lock_irq(shost->host_lock);
				vport->fc_flag |= FC_RSCN_MODE; /* RSCN still */
				spin_unlock_irq(shost->host_lock);
			}
			else
				lpfc_els_flush_rscn(vport);
		}
		lpfc_disc_start(vport);
	}
	lpfc_ct_free_iocb(phba, cmdiocb);
	return;
}