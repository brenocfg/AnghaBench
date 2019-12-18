#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ushort ;
typedef  size_t uchar ;
struct asc_board {size_t* sdtr_data; int queue_full; size_t* queue_full_cnt; } ;
struct TYPE_7__ {int pci_fix_asyn_xfer; scalar_t__* sdtr_period_tbl; size_t min_sdtr_index; size_t max_sdtr_index; int init_sdtr; int sdtr_done; int pci_fix_asyn_xfer_always; scalar_t__* cur_dvc_qng; int queue_full_or_busy; size_t* max_dvc_qng; int /*<<< orphan*/  iop_base; struct asc_board* drv_ptr; } ;
struct TYPE_6__ {scalar_t__ msg_type; scalar_t__ msg_req; scalar_t__ msg_len; scalar_t__ req_ack_offset; scalar_t__ xfer_period; scalar_t__ wdtr_width; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  TYPE_1__ EXT_MSG ;
typedef  int ASC_SCSI_BIT_ID_TYPE ;
typedef  TYPE_2__ ASC_DVC_VAR ;

/* Variables and functions */
 scalar_t__ ASCV_CURCDB_B ; 
 int /*<<< orphan*/  ASCV_HALTCODE_W ; 
 scalar_t__ ASCV_MAX_DVC_QNG_BEG ; 
 int /*<<< orphan*/  ASCV_MSGIN_BEG ; 
 int /*<<< orphan*/  ASCV_MSGOUT_BEG ; 
 scalar_t__ ASCV_SCSIBUSY_B ; 
 scalar_t__ ASC_HALT_CHK_CONDITION ; 
 scalar_t__ ASC_HALT_DISABLE_ASYN_USE_SYN_FIX ; 
 scalar_t__ ASC_HALT_ENABLE_ASYN_USE_SYN_FIX ; 
 scalar_t__ ASC_HALT_EXTMSG_IN ; 
 scalar_t__ ASC_HALT_SDTR_REJECTED ; 
 scalar_t__ ASC_HALT_SS_QUEUE_FULL ; 
 size_t ASC_MIN_TAGGED_CMD ; 
 scalar_t__ ASC_QADR_BEG ; 
 scalar_t__ ASC_QNO_TO_QADDR (size_t) ; 
 scalar_t__ ASC_SCSIQ_B_CNTL ; 
 scalar_t__ ASC_SCSIQ_B_STATUS ; 
 scalar_t__ ASC_SCSIQ_B_TAG_CODE ; 
 scalar_t__ ASC_SCSIQ_B_TARGET_IX ; 
 scalar_t__ ASC_SCSIQ_SCSI_STATUS ; 
 scalar_t__ ASC_SYN_MAX_OFFSET ; 
 size_t ASC_TAG_FLAG_DISABLE_ASYN_USE_SYN_FIX ; 
 size_t ASC_TAG_FLAG_DISABLE_DISCONNECT ; 
 scalar_t__ ASC_TID_TO_TARGET_ID (size_t) ; 
 size_t ASC_TIX_TO_TID (size_t) ; 
 size_t ASYN_SDTR_DATA_FIX_PCI_REV_AB ; 
 size_t AscCalSDTRData (TYPE_2__*,scalar_t__,scalar_t__) ; 
 size_t AscGetMCodeInitSDTRAtID (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  AscMemWordCopyPtrFromLram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int) ; 
 int /*<<< orphan*/  AscMemWordCopyPtrToLram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*,int) ; 
 int /*<<< orphan*/  AscMsgOutSDTR (TYPE_2__*,scalar_t__,size_t) ; 
 void* AscReadLramByte (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ AscReadLramWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipSDTR (int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  AscWriteLramByte (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  AscWriteLramWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EXTENDED_MESSAGE ; 
 scalar_t__ EXTENDED_SDTR ; 
 scalar_t__ EXTENDED_WDTR ; 
 scalar_t__ MESSAGE_REJECT ; 
 scalar_t__ MS_SDTR_LEN ; 
 scalar_t__ MS_WDTR_LEN ; 
 size_t QC_MSG_OUT ; 
 size_t QC_REQ_SENSE ; 
 size_t QS_BUSY ; 
 size_t QS_READY ; 
 size_t SAM_STAT_TASK_SET_FULL ; 

__attribute__((used)) static void AscIsrChipHalted(ASC_DVC_VAR *asc_dvc)
{
	EXT_MSG ext_msg;
	EXT_MSG out_msg;
	ushort halt_q_addr;
	bool sdtr_accept;
	ushort int_halt_code;
	ASC_SCSI_BIT_ID_TYPE scsi_busy;
	ASC_SCSI_BIT_ID_TYPE target_id;
	PortAddr iop_base;
	uchar tag_code;
	uchar q_status;
	uchar halt_qp;
	uchar sdtr_data;
	uchar target_ix;
	uchar q_cntl, tid_no;
	uchar cur_dvc_qng;
	uchar asyn_sdtr;
	uchar scsi_status;
	struct asc_board *boardp;

	BUG_ON(!asc_dvc->drv_ptr);
	boardp = asc_dvc->drv_ptr;

	iop_base = asc_dvc->iop_base;
	int_halt_code = AscReadLramWord(iop_base, ASCV_HALTCODE_W);

	halt_qp = AscReadLramByte(iop_base, ASCV_CURCDB_B);
	halt_q_addr = ASC_QNO_TO_QADDR(halt_qp);
	target_ix = AscReadLramByte(iop_base,
				    (ushort)(halt_q_addr +
					     (ushort)ASC_SCSIQ_B_TARGET_IX));
	q_cntl = AscReadLramByte(iop_base,
			    (ushort)(halt_q_addr + (ushort)ASC_SCSIQ_B_CNTL));
	tid_no = ASC_TIX_TO_TID(target_ix);
	target_id = (uchar)ASC_TID_TO_TARGET_ID(tid_no);
	if (asc_dvc->pci_fix_asyn_xfer & target_id) {
		asyn_sdtr = ASYN_SDTR_DATA_FIX_PCI_REV_AB;
	} else {
		asyn_sdtr = 0;
	}
	if (int_halt_code == ASC_HALT_DISABLE_ASYN_USE_SYN_FIX) {
		if (asc_dvc->pci_fix_asyn_xfer & target_id) {
			AscSetChipSDTR(iop_base, 0, tid_no);
			boardp->sdtr_data[tid_no] = 0;
		}
		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		return;
	} else if (int_halt_code == ASC_HALT_ENABLE_ASYN_USE_SYN_FIX) {
		if (asc_dvc->pci_fix_asyn_xfer & target_id) {
			AscSetChipSDTR(iop_base, asyn_sdtr, tid_no);
			boardp->sdtr_data[tid_no] = asyn_sdtr;
		}
		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		return;
	} else if (int_halt_code == ASC_HALT_EXTMSG_IN) {
		AscMemWordCopyPtrFromLram(iop_base,
					  ASCV_MSGIN_BEG,
					  (uchar *)&ext_msg,
					  sizeof(EXT_MSG) >> 1);

		if (ext_msg.msg_type == EXTENDED_MESSAGE &&
		    ext_msg.msg_req == EXTENDED_SDTR &&
		    ext_msg.msg_len == MS_SDTR_LEN) {
			sdtr_accept = true;
			if ((ext_msg.req_ack_offset > ASC_SYN_MAX_OFFSET)) {

				sdtr_accept = false;
				ext_msg.req_ack_offset = ASC_SYN_MAX_OFFSET;
			}
			if ((ext_msg.xfer_period <
			     asc_dvc->sdtr_period_tbl[asc_dvc->min_sdtr_index])
			    || (ext_msg.xfer_period >
				asc_dvc->sdtr_period_tbl[asc_dvc->
							 max_sdtr_index])) {
				sdtr_accept = false;
				ext_msg.xfer_period =
				    asc_dvc->sdtr_period_tbl[asc_dvc->
							     min_sdtr_index];
			}
			if (sdtr_accept) {
				sdtr_data =
				    AscCalSDTRData(asc_dvc, ext_msg.xfer_period,
						   ext_msg.req_ack_offset);
				if (sdtr_data == 0xFF) {

					q_cntl |= QC_MSG_OUT;
					asc_dvc->init_sdtr &= ~target_id;
					asc_dvc->sdtr_done &= ~target_id;
					AscSetChipSDTR(iop_base, asyn_sdtr,
						       tid_no);
					boardp->sdtr_data[tid_no] = asyn_sdtr;
				}
			}
			if (ext_msg.req_ack_offset == 0) {

				q_cntl &= ~QC_MSG_OUT;
				asc_dvc->init_sdtr &= ~target_id;
				asc_dvc->sdtr_done &= ~target_id;
				AscSetChipSDTR(iop_base, asyn_sdtr, tid_no);
			} else {
				if (sdtr_accept && (q_cntl & QC_MSG_OUT)) {
					q_cntl &= ~QC_MSG_OUT;
					asc_dvc->sdtr_done |= target_id;
					asc_dvc->init_sdtr |= target_id;
					asc_dvc->pci_fix_asyn_xfer &=
					    ~target_id;
					sdtr_data =
					    AscCalSDTRData(asc_dvc,
							   ext_msg.xfer_period,
							   ext_msg.
							   req_ack_offset);
					AscSetChipSDTR(iop_base, sdtr_data,
						       tid_no);
					boardp->sdtr_data[tid_no] = sdtr_data;
				} else {
					q_cntl |= QC_MSG_OUT;
					AscMsgOutSDTR(asc_dvc,
						      ext_msg.xfer_period,
						      ext_msg.req_ack_offset);
					asc_dvc->pci_fix_asyn_xfer &=
					    ~target_id;
					sdtr_data =
					    AscCalSDTRData(asc_dvc,
							   ext_msg.xfer_period,
							   ext_msg.
							   req_ack_offset);
					AscSetChipSDTR(iop_base, sdtr_data,
						       tid_no);
					boardp->sdtr_data[tid_no] = sdtr_data;
					asc_dvc->sdtr_done |= target_id;
					asc_dvc->init_sdtr |= target_id;
				}
			}

			AscWriteLramByte(iop_base,
					 (ushort)(halt_q_addr +
						  (ushort)ASC_SCSIQ_B_CNTL),
					 q_cntl);
			AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
			return;
		} else if (ext_msg.msg_type == EXTENDED_MESSAGE &&
			   ext_msg.msg_req == EXTENDED_WDTR &&
			   ext_msg.msg_len == MS_WDTR_LEN) {

			ext_msg.wdtr_width = 0;
			AscMemWordCopyPtrToLram(iop_base,
						ASCV_MSGOUT_BEG,
						(uchar *)&ext_msg,
						sizeof(EXT_MSG) >> 1);
			q_cntl |= QC_MSG_OUT;
			AscWriteLramByte(iop_base,
					 (ushort)(halt_q_addr +
						  (ushort)ASC_SCSIQ_B_CNTL),
					 q_cntl);
			AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
			return;
		} else {

			ext_msg.msg_type = MESSAGE_REJECT;
			AscMemWordCopyPtrToLram(iop_base,
						ASCV_MSGOUT_BEG,
						(uchar *)&ext_msg,
						sizeof(EXT_MSG) >> 1);
			q_cntl |= QC_MSG_OUT;
			AscWriteLramByte(iop_base,
					 (ushort)(halt_q_addr +
						  (ushort)ASC_SCSIQ_B_CNTL),
					 q_cntl);
			AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
			return;
		}
	} else if (int_halt_code == ASC_HALT_CHK_CONDITION) {

		q_cntl |= QC_REQ_SENSE;

		if ((asc_dvc->init_sdtr & target_id) != 0) {

			asc_dvc->sdtr_done &= ~target_id;

			sdtr_data = AscGetMCodeInitSDTRAtID(iop_base, tid_no);
			q_cntl |= QC_MSG_OUT;
			AscMsgOutSDTR(asc_dvc,
				      asc_dvc->
				      sdtr_period_tbl[(sdtr_data >> 4) &
						      (uchar)(asc_dvc->
							      max_sdtr_index -
							      1)],
				      (uchar)(sdtr_data & (uchar)
					      ASC_SYN_MAX_OFFSET));
		}

		AscWriteLramByte(iop_base,
				 (ushort)(halt_q_addr +
					  (ushort)ASC_SCSIQ_B_CNTL), q_cntl);

		tag_code = AscReadLramByte(iop_base,
					   (ushort)(halt_q_addr + (ushort)
						    ASC_SCSIQ_B_TAG_CODE));
		tag_code &= 0xDC;
		if ((asc_dvc->pci_fix_asyn_xfer & target_id)
		    && !(asc_dvc->pci_fix_asyn_xfer_always & target_id)
		    ) {

			tag_code |= (ASC_TAG_FLAG_DISABLE_DISCONNECT
				     | ASC_TAG_FLAG_DISABLE_ASYN_USE_SYN_FIX);

		}
		AscWriteLramByte(iop_base,
				 (ushort)(halt_q_addr +
					  (ushort)ASC_SCSIQ_B_TAG_CODE),
				 tag_code);

		q_status = AscReadLramByte(iop_base,
					   (ushort)(halt_q_addr + (ushort)
						    ASC_SCSIQ_B_STATUS));
		q_status |= (QS_READY | QS_BUSY);
		AscWriteLramByte(iop_base,
				 (ushort)(halt_q_addr +
					  (ushort)ASC_SCSIQ_B_STATUS),
				 q_status);

		scsi_busy = AscReadLramByte(iop_base, (ushort)ASCV_SCSIBUSY_B);
		scsi_busy &= ~target_id;
		AscWriteLramByte(iop_base, (ushort)ASCV_SCSIBUSY_B, scsi_busy);

		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		return;
	} else if (int_halt_code == ASC_HALT_SDTR_REJECTED) {

		AscMemWordCopyPtrFromLram(iop_base,
					  ASCV_MSGOUT_BEG,
					  (uchar *)&out_msg,
					  sizeof(EXT_MSG) >> 1);

		if ((out_msg.msg_type == EXTENDED_MESSAGE) &&
		    (out_msg.msg_len == MS_SDTR_LEN) &&
		    (out_msg.msg_req == EXTENDED_SDTR)) {

			asc_dvc->init_sdtr &= ~target_id;
			asc_dvc->sdtr_done &= ~target_id;
			AscSetChipSDTR(iop_base, asyn_sdtr, tid_no);
			boardp->sdtr_data[tid_no] = asyn_sdtr;
		}
		q_cntl &= ~QC_MSG_OUT;
		AscWriteLramByte(iop_base,
				 (ushort)(halt_q_addr +
					  (ushort)ASC_SCSIQ_B_CNTL), q_cntl);
		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		return;
	} else if (int_halt_code == ASC_HALT_SS_QUEUE_FULL) {

		scsi_status = AscReadLramByte(iop_base,
					      (ushort)((ushort)halt_q_addr +
						       (ushort)
						       ASC_SCSIQ_SCSI_STATUS));
		cur_dvc_qng =
		    AscReadLramByte(iop_base,
				    (ushort)((ushort)ASC_QADR_BEG +
					     (ushort)target_ix));
		if ((cur_dvc_qng > 0) && (asc_dvc->cur_dvc_qng[tid_no] > 0)) {

			scsi_busy = AscReadLramByte(iop_base,
						    (ushort)ASCV_SCSIBUSY_B);
			scsi_busy |= target_id;
			AscWriteLramByte(iop_base,
					 (ushort)ASCV_SCSIBUSY_B, scsi_busy);
			asc_dvc->queue_full_or_busy |= target_id;

			if (scsi_status == SAM_STAT_TASK_SET_FULL) {
				if (cur_dvc_qng > ASC_MIN_TAGGED_CMD) {
					cur_dvc_qng -= 1;
					asc_dvc->max_dvc_qng[tid_no] =
					    cur_dvc_qng;

					AscWriteLramByte(iop_base,
							 (ushort)((ushort)
								  ASCV_MAX_DVC_QNG_BEG
								  + (ushort)
								  tid_no),
							 cur_dvc_qng);

					/*
					 * Set the device queue depth to the
					 * number of active requests when the
					 * QUEUE FULL condition was encountered.
					 */
					boardp->queue_full |= target_id;
					boardp->queue_full_cnt[tid_no] =
					    cur_dvc_qng;
				}
			}
		}
		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		return;
	}
	return;
}