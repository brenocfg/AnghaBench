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
struct scsi_status_iu_header {int status; int flags; int /*<<< orphan*/  pkt_failures_length; int /*<<< orphan*/  sense_length; } ;
struct scsi_sense {int byte2; int /*<<< orphan*/  control; int /*<<< orphan*/  length; int /*<<< orphan*/ * unused; int /*<<< orphan*/  opcode; } ;
struct scb {int flags; int /*<<< orphan*/  sg_count; struct ahd_dma_seg* sg_list; scalar_t__ sense_data; struct hardware_scb* hscb; } ;
struct TYPE_5__ {scalar_t__ cdb; } ;
struct TYPE_4__ {int scsi_status; } ;
struct TYPE_6__ {TYPE_2__ idata; TYPE_1__ istatus; } ;
struct hardware_scb {int cdb_len; int /*<<< orphan*/  control; TYPE_3__ shared_data; } ;
struct ahd_transinfo {int /*<<< orphan*/  protocol_version; } ;
struct ahd_tmode_tstate {int auto_negotiate; } ;
struct ahd_softc {int /*<<< orphan*/  qfreeze_cnt; } ;
struct ahd_initiator_tinfo {struct ahd_transinfo curr; } ;
struct ahd_dma_seg {int dummy; } ;
struct ahd_devinfo {int target_mask; int /*<<< orphan*/  target; int /*<<< orphan*/  our_scsiid; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_NEG_IF_NON_ASYNC ; 
 int AHD_SHOW_SENSE ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  CAM_AUTOSENSE_FAIL ; 
 int /*<<< orphan*/  CAM_REQ_CMP_ERR ; 
 int /*<<< orphan*/  CAM_SCSI_STATUS_ERROR ; 
 int /*<<< orphan*/  KERNEL_QFREEZE_COUNT ; 
 int /*<<< orphan*/  MK_MESSAGE ; 
 int /*<<< orphan*/  REQUEST_SENSE ; 
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int SCB_ABORT ; 
 int SCB_AUTO_NEGOTIATE ; 
 int SCB_DEVICE_RESET ; 
 int /*<<< orphan*/  SCB_GET_CHANNEL (struct ahd_softc*,struct scb*) ; 
 int SCB_GET_LUN (struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_OUR_ID (struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_TAG (struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_TARGET (struct ahd_softc*,struct scb*) ; 
 int SCB_NEGOTIATE ; 
 int SCB_PKT_SENSE ; 
 int SCB_SENSE ; 
 int /*<<< orphan*/  SCSI_REV_2 ; 
#define  SCSI_STATUS_CHECK_COND 137 
#define  SCSI_STATUS_CMD_TERMINATED 136 
#define  SCSI_STATUS_OK 135 
#define  SIU_PFC_CIU_FIELDS_INVALID 134 
#define  SIU_PFC_ILLEGAL_REQUEST 133 
#define  SIU_PFC_INVALID_TYPE_CODE 132 
#define  SIU_PFC_NONE 131 
#define  SIU_PFC_TMF_FAILED 130 
#define  SIU_PFC_TMF_NOT_SUPPORTED 129 
 int /*<<< orphan*/  SIU_PKTFAIL_CODE (struct scsi_status_iu_header*) ; 
 int SIU_RSPVALID ; 
 int SIU_SNSVALID ; 
#define  STATUS_PKT_SENSE 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ahd_compile_devinfo (struct ahd_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ahd_debug ; 
 int /*<<< orphan*/  ahd_done (struct ahd_softc*,struct scb*) ; 
 struct ahd_initiator_tinfo* ahd_fetch_transinfo (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ahd_tmode_tstate**) ; 
 int /*<<< orphan*/  ahd_freeze_devq (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_freeze_scb (struct scb*) ; 
 int /*<<< orphan*/  ahd_get_residual (struct scb*) ; 
 int /*<<< orphan*/  ahd_get_sense_bufaddr (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_get_sense_bufsize (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_get_transfer_length (struct scb*) ; 
 scalar_t__ ahd_is_paused (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outw (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_pause (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_perform_autosense (struct scb*) ; 
 int /*<<< orphan*/  ahd_print_path (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_queue_scb (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_set_scsi_status (struct scb*,int) ; 
 int /*<<< orphan*/  ahd_set_transaction_status (struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_setup_data_scb (struct ahd_softc*,struct scb*) ; 
 struct ahd_dma_seg* ahd_sg_setup (struct ahd_softc*,struct scb*,struct ahd_dma_seg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_sync_sense (struct ahd_softc*,struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_unpause (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_update_neg_request (struct ahd_softc*,struct ahd_devinfo*,struct ahd_tmode_tstate*,struct ahd_initiator_tinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_update_residual (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int scsi_4btoul (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahd_handle_scsi_status(struct ahd_softc *ahd, struct scb *scb)
{
	struct	hardware_scb *hscb;
	int	paused;

	/*
	 * The sequencer freezes its select-out queue
	 * anytime a SCSI status error occurs.  We must
	 * handle the error and increment our qfreeze count
	 * to allow the sequencer to continue.  We don't
	 * bother clearing critical sections here since all
	 * operations are on data structures that the sequencer
	 * is not touching once the queue is frozen.
	 */
	hscb = scb->hscb; 

	if (ahd_is_paused(ahd)) {
		paused = 1;
	} else {
		paused = 0;
		ahd_pause(ahd);
	}

	/* Freeze the queue until the client sees the error. */
	ahd_freeze_devq(ahd, scb);
	ahd_freeze_scb(scb);
	ahd->qfreeze_cnt++;
	ahd_outw(ahd, KERNEL_QFREEZE_COUNT, ahd->qfreeze_cnt);

	if (paused == 0)
		ahd_unpause(ahd);

	/* Don't want to clobber the original sense code */
	if ((scb->flags & SCB_SENSE) != 0) {
		/*
		 * Clear the SCB_SENSE Flag and perform
		 * a normal command completion.
		 */
		scb->flags &= ~SCB_SENSE;
		ahd_set_transaction_status(scb, CAM_AUTOSENSE_FAIL);
		ahd_done(ahd, scb);
		return;
	}
	ahd_set_transaction_status(scb, CAM_SCSI_STATUS_ERROR);
	ahd_set_scsi_status(scb, hscb->shared_data.istatus.scsi_status);
	switch (hscb->shared_data.istatus.scsi_status) {
	case STATUS_PKT_SENSE:
	{
		struct scsi_status_iu_header *siu;

		ahd_sync_sense(ahd, scb, BUS_DMASYNC_POSTREAD);
		siu = (struct scsi_status_iu_header *)scb->sense_data;
		ahd_set_scsi_status(scb, siu->status);
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_SENSE) != 0) {
			ahd_print_path(ahd, scb);
			printk("SCB 0x%x Received PKT Status of 0x%x\n",
			       SCB_GET_TAG(scb), siu->status);
			printk("\tflags = 0x%x, sense len = 0x%x, "
			       "pktfail = 0x%x\n",
			       siu->flags, scsi_4btoul(siu->sense_length),
			       scsi_4btoul(siu->pkt_failures_length));
		}
#endif
		if ((siu->flags & SIU_RSPVALID) != 0) {
			ahd_print_path(ahd, scb);
			if (scsi_4btoul(siu->pkt_failures_length) < 4) {
				printk("Unable to parse pkt_failures\n");
			} else {

				switch (SIU_PKTFAIL_CODE(siu)) {
				case SIU_PFC_NONE:
					printk("No packet failure found\n");
					break;
				case SIU_PFC_CIU_FIELDS_INVALID:
					printk("Invalid Command IU Field\n");
					break;
				case SIU_PFC_TMF_NOT_SUPPORTED:
					printk("TMF not supported\n");
					break;
				case SIU_PFC_TMF_FAILED:
					printk("TMF failed\n");
					break;
				case SIU_PFC_INVALID_TYPE_CODE:
					printk("Invalid L_Q Type code\n");
					break;
				case SIU_PFC_ILLEGAL_REQUEST:
					printk("Illegal request\n");
				default:
					break;
				}
			}
			if (siu->status == SCSI_STATUS_OK)
				ahd_set_transaction_status(scb,
							   CAM_REQ_CMP_ERR);
		}
		if ((siu->flags & SIU_SNSVALID) != 0) {
			scb->flags |= SCB_PKT_SENSE;
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_SENSE) != 0)
				printk("Sense data available\n");
#endif
		}
		ahd_done(ahd, scb);
		break;
	}
	case SCSI_STATUS_CMD_TERMINATED:
	case SCSI_STATUS_CHECK_COND:
	{
		struct ahd_devinfo devinfo;
		struct ahd_dma_seg *sg;
		struct scsi_sense *sc;
		struct ahd_initiator_tinfo *targ_info;
		struct ahd_tmode_tstate *tstate;
		struct ahd_transinfo *tinfo;
#ifdef AHD_DEBUG
		if (ahd_debug & AHD_SHOW_SENSE) {
			ahd_print_path(ahd, scb);
			printk("SCB %d: requests Check Status\n",
			       SCB_GET_TAG(scb));
		}
#endif

		if (ahd_perform_autosense(scb) == 0)
			break;

		ahd_compile_devinfo(&devinfo, SCB_GET_OUR_ID(scb),
				    SCB_GET_TARGET(ahd, scb),
				    SCB_GET_LUN(scb),
				    SCB_GET_CHANNEL(ahd, scb),
				    ROLE_INITIATOR);
		targ_info = ahd_fetch_transinfo(ahd,
						devinfo.channel,
						devinfo.our_scsiid,
						devinfo.target,
						&tstate);
		tinfo = &targ_info->curr;
		sg = scb->sg_list;
		sc = (struct scsi_sense *)hscb->shared_data.idata.cdb;
		/*
		 * Save off the residual if there is one.
		 */
		ahd_update_residual(ahd, scb);
#ifdef AHD_DEBUG
		if (ahd_debug & AHD_SHOW_SENSE) {
			ahd_print_path(ahd, scb);
			printk("Sending Sense\n");
		}
#endif
		scb->sg_count = 0;
		sg = ahd_sg_setup(ahd, scb, sg, ahd_get_sense_bufaddr(ahd, scb),
				  ahd_get_sense_bufsize(ahd, scb),
				  /*last*/TRUE);
		sc->opcode = REQUEST_SENSE;
		sc->byte2 = 0;
		if (tinfo->protocol_version <= SCSI_REV_2
		 && SCB_GET_LUN(scb) < 8)
			sc->byte2 = SCB_GET_LUN(scb) << 5;
		sc->unused[0] = 0;
		sc->unused[1] = 0;
		sc->length = ahd_get_sense_bufsize(ahd, scb);
		sc->control = 0;

		/*
		 * We can't allow the target to disconnect.
		 * This will be an untagged transaction and
		 * having the target disconnect will make this
		 * transaction indestinguishable from outstanding
		 * tagged transactions.
		 */
		hscb->control = 0;

		/*
		 * This request sense could be because the
		 * the device lost power or in some other
		 * way has lost our transfer negotiations.
		 * Renegotiate if appropriate.  Unit attention
		 * errors will be reported before any data
		 * phases occur.
		 */
		if (ahd_get_residual(scb) == ahd_get_transfer_length(scb)) {
			ahd_update_neg_request(ahd, &devinfo,
					       tstate, targ_info,
					       AHD_NEG_IF_NON_ASYNC);
		}
		if (tstate->auto_negotiate & devinfo.target_mask) {
			hscb->control |= MK_MESSAGE;
			scb->flags &=
			    ~(SCB_NEGOTIATE|SCB_ABORT|SCB_DEVICE_RESET);
			scb->flags |= SCB_AUTO_NEGOTIATE;
		}
		hscb->cdb_len = sizeof(*sc);
		ahd_setup_data_scb(ahd, scb);
		scb->flags |= SCB_SENSE;
		ahd_queue_scb(ahd, scb);
		break;
	}
	case SCSI_STATUS_OK:
		printk("%s: Interrupted for status of 0???\n",
		       ahd_name(ahd));
		/* FALLTHROUGH */
	default:
		ahd_done(ahd, scb);
		break;
	}
}