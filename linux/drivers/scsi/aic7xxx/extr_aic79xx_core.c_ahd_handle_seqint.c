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
typedef  int u_int ;
struct scb {int flags; TYPE_1__* hscb; int /*<<< orphan*/  sg_count; int /*<<< orphan*/  sense_busaddr; } ;
struct ahd_transinfo {int dummy; } ;
struct ahd_tmode_tstate {int dummy; } ;
struct ahd_softc {int bugs; int msgout_len; void* msg_type; int /*<<< orphan*/  msgout_index; int /*<<< orphan*/ * msgout_buf; int /*<<< orphan*/  msgin_index; } ;
struct ahd_initiator_tinfo {struct ahd_transinfo curr; } ;
struct ahd_devinfo {int /*<<< orphan*/  lun; int /*<<< orphan*/  target; int /*<<< orphan*/  channel; int /*<<< orphan*/  role; int /*<<< orphan*/  our_scsiid; } ;
typedef  int /*<<< orphan*/  cam_status ;
struct TYPE_4__ {int phasemsg; } ;
struct TYPE_3__ {int scsiid; int lun; int control; int /*<<< orphan*/  task_management; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCUM ; 
 int /*<<< orphan*/  AC_SENT_BDR ; 
 int /*<<< orphan*/  AHD_ASSERT_MODES (struct ahd_softc*,int,int) ; 
 int AHD_CLRLQO_AUTOCLR_BUG ; 
 int AHD_INTCOLLISION_BUG ; 
 int AHD_MODE_CFG_MSK ; 
 int /*<<< orphan*/  AHD_MODE_SCSI ; 
 int AHD_MODE_SCSI_MSK ; 
 int AHD_MODE_UNKNOWN_MSK ; 
 int /*<<< orphan*/  AHD_SENSE_BUFSIZE ; 
 int AHD_SHOW_MISC ; 
 int AHD_SHOW_RECOVERY ; 
 int /*<<< orphan*/  AHD_TRANS_ACTIVE ; 
 int ATNO ; 
#define  BAD_PHASE 164 
 int /*<<< orphan*/  BUILD_TCL (int,int) ; 
 int /*<<< orphan*/  CAM_BDR_SENT ; 
 int /*<<< orphan*/  CAM_DATA_RUN_ERR ; 
 int CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
#define  CFG4ISTAT_INTR 163 
#define  CFG4OVERRUN 162 
 int /*<<< orphan*/  CLRINT ; 
 int /*<<< orphan*/  CLRLQOINT1 ; 
 int CLRLQOPHACHGINPKT ; 
 int CLRSEQINT ; 
#define  DATA_OVERRUN 161 
 int /*<<< orphan*/  DFCNTRL ; 
 int DPHASE ; 
#define  DUMP_CARD_STATE 160 
 int ENSELO ; 
#define  ENTERING_NONPACK 159 
 int /*<<< orphan*/  HADDR ; 
 int /*<<< orphan*/  HCNT ; 
 int HDMAEN ; 
 int HOST_MSG ; 
#define  HOST_MSG_LOOP 158 
#define  IGN_WIDE_RES 157 
#define  ILLEGAL_PHASE 156 
#define  INVALID_SEQINT 155 
 int /*<<< orphan*/  LASTPHASE ; 
 int LQIPHASE_OUTPKT ; 
 int /*<<< orphan*/  LQISTAT2 ; 
#define  MISSED_BUSFREE 154 
#define  MKMSG_FAILED 153 
 int MK_MESSAGE ; 
 int /*<<< orphan*/  MODE_PTR ; 
 int /*<<< orphan*/  MSG_ABORT_TASK ; 
 int /*<<< orphan*/  MSG_BUS_DEV_RESET ; 
 int /*<<< orphan*/  MSG_EXT_WDTR_BUS_8_BIT ; 
 int /*<<< orphan*/  MSG_OUT ; 
 void* MSG_TYPE_INITIATOR_MSGIN ; 
 void* MSG_TYPE_INITIATOR_MSGOUT ; 
 void* MSG_TYPE_NONE ; 
 void* MSG_TYPE_TARGET_MSGOUT ; 
#define  NO_MATCH 152 
#define  NO_SEQINT 151 
#define  PDATA_REINIT 150 
 int PHASE_MASK ; 
 int PRELOADEN ; 
#define  PROTO_VIOLATION 149 
#define  P_COMMAND 148 
#define  P_DATAIN 147 
#define  P_DATAIN_DT 146 
#define  P_DATAOUT 145 
#define  P_DATAOUT_DT 144 
#define  P_MESGIN 143 
#define  P_MESGOUT 142 
#define  P_STATUS 141 
 int /*<<< orphan*/  REG0 ; 
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int /*<<< orphan*/  SAVED_LUN ; 
 int /*<<< orphan*/  SAVED_SCSIID ; 
#define  SAW_HWERR 140 
 int SCB_ABORT ; 
 int /*<<< orphan*/  SCB_CDB_LEN ; 
 int /*<<< orphan*/  SCB_CDB_STORE ; 
 int /*<<< orphan*/  SCB_CONTROL ; 
 int SCB_EXTERNAL_RESET ; 
 int /*<<< orphan*/  SCB_GET_CHANNEL (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_LUN (struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_OUR_ID (struct scb*) ; 
 int SCB_GET_TAG (struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_TARGET (struct ahd_softc*,struct scb*) ; 
 int SCB_LIST_NULL ; 
 int /*<<< orphan*/  SCB_LUN ; 
 int SCB_PACKETIZED ; 
 int SCB_RECOVERY_SCB ; 
 int /*<<< orphan*/  SCB_SCSIID ; 
 int SCB_TAG_TYPE ; 
 int /*<<< orphan*/  SCB_TASK_MANAGEMENT ; 
 int /*<<< orphan*/  SCSIBUS ; 
 int SCSIEN ; 
 int /*<<< orphan*/  SCSIID_TARGET (struct ahd_softc*,int) ; 
 int /*<<< orphan*/  SCSISEQ0 ; 
 int /*<<< orphan*/  SCSISIGI ; 
 int /*<<< orphan*/  SCSISIGO ; 
 int /*<<< orphan*/  SEARCH_REMOVE ; 
 int SELDO ; 
 int /*<<< orphan*/  SELID ; 
 int SELTO ; 
 int /*<<< orphan*/  SEQCTL0 ; 
 int /*<<< orphan*/  SEQINTCODE ; 
 int /*<<< orphan*/  SEQ_FLAGS ; 
 int /*<<< orphan*/  SG_CACHE_PRE ; 
 int /*<<< orphan*/  SG_CACHE_SHADOW ; 
 int SG_LAST_SEG ; 
 int /*<<< orphan*/  SINDEX ; 
#define  SIU_TASKMGMT_ABORT_TASK 139 
#define  SIU_TASKMGMT_ABORT_TASK_SET 138 
#define  SIU_TASKMGMT_CLEAR_TASK_SET 137 
#define  SIU_TASKMGMT_LUN_RESET 136 
#define  SIU_TASKMGMT_TARGET_RESET 135 
 int /*<<< orphan*/  SSTAT0 ; 
 int /*<<< orphan*/  SSTAT1 ; 
#define  STATUS_OVERRUN 134 
 int STATUS_RCVD ; 
 int /*<<< orphan*/  SXFRCTL0 ; 
 int TAG_ENB ; 
#define  TASKMGMT_CMD_CMPLT_OKAY 133 
#define  TASKMGMT_FUNC_COMPLETE 132 
#define  TRACEPOINT0 131 
#define  TRACEPOINT1 130 
#define  TRACEPOINT2 129 
#define  TRACEPOINT3 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ahd_abort_scbs (struct ahd_softc*,int /*<<< orphan*/ ,char,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_assert_atn (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_clear_intstat (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_compile_devinfo (struct ahd_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ahd_debug ; 
 int /*<<< orphan*/  ahd_dump_card_state (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_dump_sglist (struct scb*) ; 
 int /*<<< orphan*/  ahd_fetch_devinfo (struct ahd_softc*,struct ahd_devinfo*) ; 
 struct ahd_initiator_tinfo* ahd_fetch_transinfo (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ahd_tmode_tstate**) ; 
 int /*<<< orphan*/  ahd_find_busy_tcl (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_freeze_devq (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_freeze_scb (struct scb*) ; 
 int ahd_get_scbptr (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_get_transfer_length (struct scb*) ; 
 int /*<<< orphan*/  ahd_handle_devreset (struct ahd_softc*,struct ahd_devinfo*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_handle_hwerrint (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_handle_ign_wide_residue (struct ahd_softc*,struct ahd_devinfo*) ; 
 int /*<<< orphan*/  ahd_handle_message_phase (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_handle_proto_violation (struct ahd_softc*) ; 
 int ahd_inb (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int ahd_inb_scbram (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_inw (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_is_paused (struct ahd_softc*) ; 
 TYPE_2__* ahd_lookup_phase_entry (int) ; 
 struct scb* ahd_lookup_scb (struct ahd_softc*,int) ; 
 int ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ahd_outq (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_outw (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_print_path (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_reinitialize_dataptrs (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_reset_channel (struct ahd_softc*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_restart (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_scb_devinfo (struct ahd_softc*,struct ahd_devinfo*,struct scb*) ; 
 int /*<<< orphan*/  ahd_search_qinfifo (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_send_async (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_modes (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_syncrate (struct ahd_softc*,struct ahd_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_transaction_status (struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_width (struct ahd_softc*,struct ahd_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_setup_initiator_msgout (struct ahd_softc*,struct ahd_devinfo*,struct scb*) ; 
 int /*<<< orphan*/  ahd_setup_target_msgin (struct ahd_softc*,struct ahd_devinfo*,struct scb*) ; 
 int /*<<< orphan*/  ahd_unpause (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_update_modes (struct ahd_softc*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void
ahd_handle_seqint(struct ahd_softc *ahd, u_int intstat)
{
	u_int seqintcode;

	/*
	 * Save the sequencer interrupt code and clear the SEQINT
	 * bit. We will unpause the sequencer, if appropriate,
	 * after servicing the request.
	 */
	seqintcode = ahd_inb(ahd, SEQINTCODE);
	ahd_outb(ahd, CLRINT, CLRSEQINT);
	if ((ahd->bugs & AHD_INTCOLLISION_BUG) != 0) {
		/*
		 * Unpause the sequencer and let it clear
		 * SEQINT by writing NO_SEQINT to it.  This
		 * will cause the sequencer to be paused again,
		 * which is the expected state of this routine.
		 */
		ahd_unpause(ahd);
		while (!ahd_is_paused(ahd))
			;
		ahd_outb(ahd, CLRINT, CLRSEQINT);
	}
	ahd_update_modes(ahd);
#ifdef AHD_DEBUG
	if ((ahd_debug & AHD_SHOW_MISC) != 0)
		printk("%s: Handle Seqint Called for code %d\n",
		       ahd_name(ahd), seqintcode);
#endif
	switch (seqintcode) {
	case ENTERING_NONPACK:
	{
		struct	scb *scb;
		u_int	scbid;

		AHD_ASSERT_MODES(ahd, ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK),
				 ~(AHD_MODE_UNKNOWN_MSK|AHD_MODE_CFG_MSK));
		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		if (scb == NULL) {
			/*
			 * Somehow need to know if this
			 * is from a selection or reselection.
			 * From that, we can determine target
			 * ID so we at least have an I_T nexus.
			 */
		} else {
			ahd_outb(ahd, SAVED_SCSIID, scb->hscb->scsiid);
			ahd_outb(ahd, SAVED_LUN, scb->hscb->lun);
			ahd_outb(ahd, SEQ_FLAGS, 0x0);
		}
		if ((ahd_inb(ahd, LQISTAT2) & LQIPHASE_OUTPKT) != 0
		 && (ahd_inb(ahd, SCSISIGO) & ATNO) != 0) {
			/*
			 * Phase change after read stream with
			 * CRC error with P0 asserted on last
			 * packet.
			 */
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_RECOVERY) != 0)
				printk("%s: Assuming LQIPHASE_NLQ with "
				       "P0 assertion\n", ahd_name(ahd));
#endif
		}
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_RECOVERY) != 0)
			printk("%s: Entering NONPACK\n", ahd_name(ahd));
#endif
		break;
	}
	case INVALID_SEQINT:
		printk("%s: Invalid Sequencer interrupt occurred, "
		       "resetting channel.\n",
		       ahd_name(ahd));
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_RECOVERY) != 0)
			ahd_dump_card_state(ahd);
#endif
		ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
		break;
	case STATUS_OVERRUN:
	{
		struct	scb *scb;
		u_int	scbid;

		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		if (scb != NULL)
			ahd_print_path(ahd, scb);
		else
			printk("%s: ", ahd_name(ahd));
		printk("SCB %d Packetized Status Overrun", scbid);
		ahd_dump_card_state(ahd);
		ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
		break;
	}
	case CFG4ISTAT_INTR:
	{
		struct	scb *scb;
		u_int	scbid;

		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		if (scb == NULL) {
			ahd_dump_card_state(ahd);
			printk("CFG4ISTAT: Free SCB %d referenced", scbid);
			panic("For safety");
		}
		ahd_outq(ahd, HADDR, scb->sense_busaddr);
		ahd_outw(ahd, HCNT, AHD_SENSE_BUFSIZE);
		ahd_outb(ahd, HCNT + 2, 0);
		ahd_outb(ahd, SG_CACHE_PRE, SG_LAST_SEG);
		ahd_outb(ahd, DFCNTRL, PRELOADEN|SCSIEN|HDMAEN);
		break;
	}
	case ILLEGAL_PHASE:
	{
		u_int bus_phase;

		bus_phase = ahd_inb(ahd, SCSISIGI) & PHASE_MASK;
		printk("%s: ILLEGAL_PHASE 0x%x\n",
		       ahd_name(ahd), bus_phase);

		switch (bus_phase) {
		case P_DATAOUT:
		case P_DATAIN:
		case P_DATAOUT_DT:
		case P_DATAIN_DT:
		case P_MESGOUT:
		case P_STATUS:
		case P_MESGIN:
			ahd_reset_channel(ahd, 'A', /*Initiate Reset*/TRUE);
			printk("%s: Issued Bus Reset.\n", ahd_name(ahd));
			break;
		case P_COMMAND:
		{
			struct	ahd_devinfo devinfo;
			struct	scb *scb;
			struct	ahd_initiator_tinfo *targ_info;
			struct	ahd_tmode_tstate *tstate;
			struct	ahd_transinfo *tinfo;
			u_int	scbid;

			/*
			 * If a target takes us into the command phase
			 * assume that it has been externally reset and
			 * has thus lost our previous packetized negotiation
			 * agreement.  Since we have not sent an identify
			 * message and may not have fully qualified the
			 * connection, we change our command to TUR, assert
			 * ATN and ABORT the task when we go to message in
			 * phase.  The OSM will see the REQUEUE_REQUEST
			 * status and retry the command.
			 */
			scbid = ahd_get_scbptr(ahd);
			scb = ahd_lookup_scb(ahd, scbid);
			if (scb == NULL) {
				printk("Invalid phase with no valid SCB.  "
				       "Resetting bus.\n");
				ahd_reset_channel(ahd, 'A',
						  /*Initiate Reset*/TRUE);
				break;
			}
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
			ahd_set_width(ahd, &devinfo, MSG_EXT_WDTR_BUS_8_BIT,
				      AHD_TRANS_ACTIVE, /*paused*/TRUE);
			ahd_set_syncrate(ahd, &devinfo, /*period*/0,
					 /*offset*/0, /*ppr_options*/0,
					 AHD_TRANS_ACTIVE, /*paused*/TRUE);
			/* Hand-craft TUR command */
			ahd_outb(ahd, SCB_CDB_STORE, 0);
			ahd_outb(ahd, SCB_CDB_STORE+1, 0);
			ahd_outb(ahd, SCB_CDB_STORE+2, 0);
			ahd_outb(ahd, SCB_CDB_STORE+3, 0);
			ahd_outb(ahd, SCB_CDB_STORE+4, 0);
			ahd_outb(ahd, SCB_CDB_STORE+5, 0);
			ahd_outb(ahd, SCB_CDB_LEN, 6);
			scb->hscb->control &= ~(TAG_ENB|SCB_TAG_TYPE);
			scb->hscb->control |= MK_MESSAGE;
			ahd_outb(ahd, SCB_CONTROL, scb->hscb->control);
			ahd_outb(ahd, MSG_OUT, HOST_MSG);
			ahd_outb(ahd, SAVED_SCSIID, scb->hscb->scsiid);
			/*
			 * The lun is 0, regardless of the SCB's lun
			 * as we have not sent an identify message.
			 */
			ahd_outb(ahd, SAVED_LUN, 0);
			ahd_outb(ahd, SEQ_FLAGS, 0);
			ahd_assert_atn(ahd);
			scb->flags &= ~SCB_PACKETIZED;
			scb->flags |= SCB_ABORT|SCB_EXTERNAL_RESET;
			ahd_freeze_devq(ahd, scb);
			ahd_set_transaction_status(scb, CAM_REQUEUE_REQ);
			ahd_freeze_scb(scb);

			/* Notify XPT */
			ahd_send_async(ahd, devinfo.channel, devinfo.target,
				       CAM_LUN_WILDCARD, AC_SENT_BDR);

			/*
			 * Allow the sequencer to continue with
			 * non-pack processing.
			 */
			ahd_set_modes(ahd, AHD_MODE_SCSI, AHD_MODE_SCSI);
			ahd_outb(ahd, CLRLQOINT1, CLRLQOPHACHGINPKT);
			if ((ahd->bugs & AHD_CLRLQO_AUTOCLR_BUG) != 0) {
				ahd_outb(ahd, CLRLQOINT1, 0);
			}
#ifdef AHD_DEBUG
			if ((ahd_debug & AHD_SHOW_RECOVERY) != 0) {
				ahd_print_path(ahd, scb);
				printk("Unexpected command phase from "
				       "packetized target\n");
			}
#endif
			break;
		}
		}
		break;
	}
	case CFG4OVERRUN:
	{
		struct	scb *scb;
		u_int	scb_index;
		
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_RECOVERY) != 0) {
			printk("%s: CFG4OVERRUN mode = %x\n", ahd_name(ahd),
			       ahd_inb(ahd, MODE_PTR));
		}
#endif
		scb_index = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scb_index);
		if (scb == NULL) {
			/*
			 * Attempt to transfer to an SCB that is
			 * not outstanding.
			 */
			ahd_assert_atn(ahd);
			ahd_outb(ahd, MSG_OUT, HOST_MSG);
			ahd->msgout_buf[0] = MSG_ABORT_TASK;
			ahd->msgout_len = 1;
			ahd->msgout_index = 0;
			ahd->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
			/*
			 * Clear status received flag to prevent any
			 * attempt to complete this bogus SCB.
			 */
			ahd_outb(ahd, SCB_CONTROL,
				 ahd_inb_scbram(ahd, SCB_CONTROL)
				 & ~STATUS_RCVD);
		}
		break;
	}
	case DUMP_CARD_STATE:
	{
		ahd_dump_card_state(ahd);
		break;
	}
	case PDATA_REINIT:
	{
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_RECOVERY) != 0) {
			printk("%s: PDATA_REINIT - DFCNTRL = 0x%x "
			       "SG_CACHE_SHADOW = 0x%x\n",
			       ahd_name(ahd), ahd_inb(ahd, DFCNTRL),
			       ahd_inb(ahd, SG_CACHE_SHADOW));
		}
#endif
		ahd_reinitialize_dataptrs(ahd);
		break;
	}
	case HOST_MSG_LOOP:
	{
		struct ahd_devinfo devinfo;

		/*
		 * The sequencer has encountered a message phase
		 * that requires host assistance for completion.
		 * While handling the message phase(s), we will be
		 * notified by the sequencer after each byte is
		 * transferred so we can track bus phase changes.
		 *
		 * If this is the first time we've seen a HOST_MSG_LOOP
		 * interrupt, initialize the state of the host message
		 * loop.
		 */
		ahd_fetch_devinfo(ahd, &devinfo);
		if (ahd->msg_type == MSG_TYPE_NONE) {
			struct scb *scb;
			u_int scb_index;
			u_int bus_phase;

			bus_phase = ahd_inb(ahd, SCSISIGI) & PHASE_MASK;
			if (bus_phase != P_MESGIN
			 && bus_phase != P_MESGOUT) {
				printk("ahd_intr: HOST_MSG_LOOP bad "
				       "phase 0x%x\n", bus_phase);
				/*
				 * Probably transitioned to bus free before
				 * we got here.  Just punt the message.
				 */
				ahd_dump_card_state(ahd);
				ahd_clear_intstat(ahd);
				ahd_restart(ahd);
				return;
			}

			scb_index = ahd_get_scbptr(ahd);
			scb = ahd_lookup_scb(ahd, scb_index);
			if (devinfo.role == ROLE_INITIATOR) {
				if (bus_phase == P_MESGOUT)
					ahd_setup_initiator_msgout(ahd,
								   &devinfo,
								   scb);
				else {
					ahd->msg_type =
					    MSG_TYPE_INITIATOR_MSGIN;
					ahd->msgin_index = 0;
				}
			}
#ifdef AHD_TARGET_MODE
			else {
				if (bus_phase == P_MESGOUT) {
					ahd->msg_type =
					    MSG_TYPE_TARGET_MSGOUT;
					ahd->msgin_index = 0;
				}
				else 
					ahd_setup_target_msgin(ahd,
							       &devinfo,
							       scb);
			}
#endif
		}

		ahd_handle_message_phase(ahd);
		break;
	}
	case NO_MATCH:
	{
		/* Ensure we don't leave the selection hardware on */
		AHD_ASSERT_MODES(ahd, AHD_MODE_SCSI_MSK, AHD_MODE_SCSI_MSK);
		ahd_outb(ahd, SCSISEQ0, ahd_inb(ahd, SCSISEQ0) & ~ENSELO);

		printk("%s:%c:%d: no active SCB for reconnecting "
		       "target - issuing BUS DEVICE RESET\n",
		       ahd_name(ahd), 'A', ahd_inb(ahd, SELID) >> 4);
		printk("SAVED_SCSIID == 0x%x, SAVED_LUN == 0x%x, "
		       "REG0 == 0x%x ACCUM = 0x%x\n",
		       ahd_inb(ahd, SAVED_SCSIID), ahd_inb(ahd, SAVED_LUN),
		       ahd_inw(ahd, REG0), ahd_inb(ahd, ACCUM));
		printk("SEQ_FLAGS == 0x%x, SCBPTR == 0x%x, BTT == 0x%x, "
		       "SINDEX == 0x%x\n",
		       ahd_inb(ahd, SEQ_FLAGS), ahd_get_scbptr(ahd),
		       ahd_find_busy_tcl(ahd,
					 BUILD_TCL(ahd_inb(ahd, SAVED_SCSIID),
						   ahd_inb(ahd, SAVED_LUN))),
		       ahd_inw(ahd, SINDEX));
		printk("SELID == 0x%x, SCB_SCSIID == 0x%x, SCB_LUN == 0x%x, "
		       "SCB_CONTROL == 0x%x\n",
		       ahd_inb(ahd, SELID), ahd_inb_scbram(ahd, SCB_SCSIID),
		       ahd_inb_scbram(ahd, SCB_LUN),
		       ahd_inb_scbram(ahd, SCB_CONTROL));
		printk("SCSIBUS[0] == 0x%x, SCSISIGI == 0x%x\n",
		       ahd_inb(ahd, SCSIBUS), ahd_inb(ahd, SCSISIGI));
		printk("SXFRCTL0 == 0x%x\n", ahd_inb(ahd, SXFRCTL0));
		printk("SEQCTL0 == 0x%x\n", ahd_inb(ahd, SEQCTL0));
		ahd_dump_card_state(ahd);
		ahd->msgout_buf[0] = MSG_BUS_DEV_RESET;
		ahd->msgout_len = 1;
		ahd->msgout_index = 0;
		ahd->msg_type = MSG_TYPE_INITIATOR_MSGOUT;
		ahd_outb(ahd, MSG_OUT, HOST_MSG);
		ahd_assert_atn(ahd);
		break;
	}
	case PROTO_VIOLATION:
	{
		ahd_handle_proto_violation(ahd);
		break;
	}
	case IGN_WIDE_RES:
	{
		struct ahd_devinfo devinfo;

		ahd_fetch_devinfo(ahd, &devinfo);
		ahd_handle_ign_wide_residue(ahd, &devinfo);
		break;
	}
	case BAD_PHASE:
	{
		u_int lastphase;

		lastphase = ahd_inb(ahd, LASTPHASE);
		printk("%s:%c:%d: unknown scsi bus phase %x, "
		       "lastphase = 0x%x.  Attempting to continue\n",
		       ahd_name(ahd), 'A',
		       SCSIID_TARGET(ahd, ahd_inb(ahd, SAVED_SCSIID)),
		       lastphase, ahd_inb(ahd, SCSISIGI));
		break;
	}
	case MISSED_BUSFREE:
	{
		u_int lastphase;

		lastphase = ahd_inb(ahd, LASTPHASE);
		printk("%s:%c:%d: Missed busfree. "
		       "Lastphase = 0x%x, Curphase = 0x%x\n",
		       ahd_name(ahd), 'A',
		       SCSIID_TARGET(ahd, ahd_inb(ahd, SAVED_SCSIID)),
		       lastphase, ahd_inb(ahd, SCSISIGI));
		ahd_restart(ahd);
		return;
	}
	case DATA_OVERRUN:
	{
		/*
		 * When the sequencer detects an overrun, it
		 * places the controller in "BITBUCKET" mode
		 * and allows the target to complete its transfer.
		 * Unfortunately, none of the counters get updated
		 * when the controller is in this mode, so we have
		 * no way of knowing how large the overrun was.
		 */
		struct	scb *scb;
		u_int	scbindex;
#ifdef AHD_DEBUG
		u_int	lastphase;
#endif

		scbindex = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbindex);
#ifdef AHD_DEBUG
		lastphase = ahd_inb(ahd, LASTPHASE);
		if ((ahd_debug & AHD_SHOW_RECOVERY) != 0) {
			ahd_print_path(ahd, scb);
			printk("data overrun detected %s.  Tag == 0x%x.\n",
			       ahd_lookup_phase_entry(lastphase)->phasemsg,
			       SCB_GET_TAG(scb));
			ahd_print_path(ahd, scb);
			printk("%s seen Data Phase.  Length = %ld.  "
			       "NumSGs = %d.\n",
			       ahd_inb(ahd, SEQ_FLAGS) & DPHASE
			       ? "Have" : "Haven't",
			       ahd_get_transfer_length(scb), scb->sg_count);
			ahd_dump_sglist(scb);
		}
#endif

		/*
		 * Set this and it will take effect when the
		 * target does a command complete.
		 */
		ahd_freeze_devq(ahd, scb);
		ahd_set_transaction_status(scb, CAM_DATA_RUN_ERR);
		ahd_freeze_scb(scb);
		break;
	}
	case MKMSG_FAILED:
	{
		struct ahd_devinfo devinfo;
		struct scb *scb;
		u_int scbid;

		ahd_fetch_devinfo(ahd, &devinfo);
		printk("%s:%c:%d:%d: Attempt to issue message failed\n",
		       ahd_name(ahd), devinfo.channel, devinfo.target,
		       devinfo.lun);
		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		if (scb != NULL
		 && (scb->flags & SCB_RECOVERY_SCB) != 0)
			/*
			 * Ensure that we didn't put a second instance of this
			 * SCB into the QINFIFO.
			 */
			ahd_search_qinfifo(ahd, SCB_GET_TARGET(ahd, scb),
					   SCB_GET_CHANNEL(ahd, scb),
					   SCB_GET_LUN(scb), SCB_GET_TAG(scb),
					   ROLE_INITIATOR, /*status*/0,
					   SEARCH_REMOVE);
		ahd_outb(ahd, SCB_CONTROL,
			 ahd_inb_scbram(ahd, SCB_CONTROL) & ~MK_MESSAGE);
		break;
	}
	case TASKMGMT_FUNC_COMPLETE:
	{
		u_int	scbid;
		struct	scb *scb;

		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		if (scb != NULL) {
			u_int	   lun;
			u_int	   tag;
			cam_status error;

			ahd_print_path(ahd, scb);
			printk("Task Management Func 0x%x Complete\n",
			       scb->hscb->task_management);
			lun = CAM_LUN_WILDCARD;
			tag = SCB_LIST_NULL;

			switch (scb->hscb->task_management) {
			case SIU_TASKMGMT_ABORT_TASK:
				tag = SCB_GET_TAG(scb);
				/* fall through */
			case SIU_TASKMGMT_ABORT_TASK_SET:
			case SIU_TASKMGMT_CLEAR_TASK_SET:
				lun = scb->hscb->lun;
				error = CAM_REQ_ABORTED;
				ahd_abort_scbs(ahd, SCB_GET_TARGET(ahd, scb),
					       'A', lun, tag, ROLE_INITIATOR,
					       error);
				break;
			case SIU_TASKMGMT_LUN_RESET:
				lun = scb->hscb->lun;
				/* fall through */
			case SIU_TASKMGMT_TARGET_RESET:
			{
				struct ahd_devinfo devinfo;

				ahd_scb_devinfo(ahd, &devinfo, scb);
				error = CAM_BDR_SENT;
				ahd_handle_devreset(ahd, &devinfo, lun,
						    CAM_BDR_SENT,
						    lun != CAM_LUN_WILDCARD
						    ? "Lun Reset"
						    : "Target Reset",
						    /*verbose_level*/0);
				break;
			}
			default:
				panic("Unexpected TaskMgmt Func\n");
				break;
			}
		}
		break;
	}
	case TASKMGMT_CMD_CMPLT_OKAY:
	{
		u_int	scbid;
		struct	scb *scb;

		/*
		 * An ABORT TASK TMF failed to be delivered before
		 * the targeted command completed normally.
		 */
		scbid = ahd_get_scbptr(ahd);
		scb = ahd_lookup_scb(ahd, scbid);
		if (scb != NULL) {
			/*
			 * Remove the second instance of this SCB from
			 * the QINFIFO if it is still there.
                         */
			ahd_print_path(ahd, scb);
			printk("SCB completes before TMF\n");
			/*
			 * Handle losing the race.  Wait until any
			 * current selection completes.  We will then
			 * set the TMF back to zero in this SCB so that
			 * the sequencer doesn't bother to issue another
			 * sequencer interrupt for its completion.
			 */
			while ((ahd_inb(ahd, SCSISEQ0) & ENSELO) != 0
			    && (ahd_inb(ahd, SSTAT0) & SELDO) == 0
			    && (ahd_inb(ahd, SSTAT1) & SELTO) == 0)
				;
			ahd_outb(ahd, SCB_TASK_MANAGEMENT, 0);
			ahd_search_qinfifo(ahd, SCB_GET_TARGET(ahd, scb),
					   SCB_GET_CHANNEL(ahd, scb),  
					   SCB_GET_LUN(scb), SCB_GET_TAG(scb), 
					   ROLE_INITIATOR, /*status*/0,   
					   SEARCH_REMOVE);
		}
		break;
	}
	case TRACEPOINT0:
	case TRACEPOINT1:
	case TRACEPOINT2:
	case TRACEPOINT3:
		printk("%s: Tracepoint %d\n", ahd_name(ahd),
		       seqintcode - TRACEPOINT0);
		break;
	case NO_SEQINT:
		break;
	case SAW_HWERR:
		ahd_handle_hwerrint(ahd);
		break;
	default:
		printk("%s: Unexpected SEQINTCODE %d\n", ahd_name(ahd),
		       seqintcode);
		break;
	}
	/*
	 *  The sequencer is paused immediately on
	 *  a SEQINT, so we should restart it when
	 *  we're done.
	 */
	ahd_unpause(ahd);
}