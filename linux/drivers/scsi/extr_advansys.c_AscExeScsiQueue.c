#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int ushort ;
typedef  int uint ;
typedef  int uchar ;
typedef  unsigned long u32 ;
struct TYPE_19__ {scalar_t__ err_code; int init_sdtr; int sdtr_done; int max_sdtr_index; scalar_t__ in_critical_cnt; int pci_fix_asyn_xfer; int pci_fix_asyn_xfer_always; int bug_fix_cntl; int /*<<< orphan*/ * sdtr_period_tbl; int /*<<< orphan*/  iop_base; } ;
struct TYPE_16__ {int extra_bytes; int target_id; int cntl; unsigned long data_addr; unsigned long data_cnt; scalar_t__ q_no; } ;
struct TYPE_14__ {int tag_code; int target_ix; } ;
struct TYPE_18__ {scalar_t__* cdbptr; TYPE_3__ q1; TYPE_1__ q2; TYPE_4__* sg_head; } ;
struct TYPE_17__ {int entry_cnt; int entry_to_copy; TYPE_2__* sg_list; } ;
struct TYPE_15__ {unsigned long addr; unsigned long bytes; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  TYPE_4__ ASC_SG_HEAD ;
typedef  TYPE_5__ ASC_SCSI_Q ;
typedef  TYPE_6__ ASC_DVC_VAR ;

/* Variables and functions */
 int /*<<< orphan*/  ASCQ_ERR_CRITICAL_RE_ENTRY ; 
 int ASC_BUG_FIX_IF_NOT_DWB ; 
 int ASC_ERROR ; 
 int ASC_MAX_SG_LIST ; 
 scalar_t__ ASC_SYN_MAX_OFFSET ; 
 int ASC_SYN_OFFSET_ONE_DISABLE_LIST ; 
 int ASC_TAG_FLAG_DISABLE_ASYN_USE_SYN_FIX ; 
 int ASC_TAG_FLAG_DISABLE_DISCONNECT ; 
 int ASC_TAG_FLAG_EXTRA_BYTES ; 
 int ASC_TIX_TO_TID (int) ; 
 int AscGetMCodeInitSDTRAtID (int /*<<< orphan*/ ,int) ; 
 int AscGetNumOfFreeQueue (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  AscMsgOutSDTR (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int AscSendScsiQueue (TYPE_6__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  AscSetLibErrorCode (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int AscSgListToQueue (int) ; 
 int QC_MSG_OUT ; 
 int QC_SG_HEAD ; 
 int QC_SG_SWAP_QUEUE ; 
 int QC_URGENT ; 
 int READ_10 ; 
 int READ_6 ; 
 scalar_t__ REQUEST_SENSE ; 
 int SIMPLE_QUEUE_TAG ; 
 int* _syn_offset_one_disable_cmd ; 
 void* cpu_to_le32 (unsigned long) ; 
 unsigned long le32_to_cpu (unsigned long) ; 

__attribute__((used)) static int AscExeScsiQueue(ASC_DVC_VAR *asc_dvc, ASC_SCSI_Q *scsiq)
{
	PortAddr iop_base;
	int sta;
	int n_q_required;
	bool disable_syn_offset_one_fix;
	int i;
	u32 addr;
	ushort sg_entry_cnt = 0;
	ushort sg_entry_cnt_minus_one = 0;
	uchar target_ix;
	uchar tid_no;
	uchar sdtr_data;
	uchar extra_bytes;
	uchar scsi_cmd;
	uchar disable_cmd;
	ASC_SG_HEAD *sg_head;
	unsigned long data_cnt;

	iop_base = asc_dvc->iop_base;
	sg_head = scsiq->sg_head;
	if (asc_dvc->err_code != 0)
		return ASC_ERROR;
	scsiq->q1.q_no = 0;
	if ((scsiq->q2.tag_code & ASC_TAG_FLAG_EXTRA_BYTES) == 0) {
		scsiq->q1.extra_bytes = 0;
	}
	sta = 0;
	target_ix = scsiq->q2.target_ix;
	tid_no = ASC_TIX_TO_TID(target_ix);
	n_q_required = 1;
	if (scsiq->cdbptr[0] == REQUEST_SENSE) {
		if ((asc_dvc->init_sdtr & scsiq->q1.target_id) != 0) {
			asc_dvc->sdtr_done &= ~scsiq->q1.target_id;
			sdtr_data = AscGetMCodeInitSDTRAtID(iop_base, tid_no);
			AscMsgOutSDTR(asc_dvc,
				      asc_dvc->
				      sdtr_period_tbl[(sdtr_data >> 4) &
						      (uchar)(asc_dvc->
							      max_sdtr_index -
							      1)],
				      (uchar)(sdtr_data & (uchar)
					      ASC_SYN_MAX_OFFSET));
			scsiq->q1.cntl |= (QC_MSG_OUT | QC_URGENT);
		}
	}
	if (asc_dvc->in_critical_cnt != 0) {
		AscSetLibErrorCode(asc_dvc, ASCQ_ERR_CRITICAL_RE_ENTRY);
		return ASC_ERROR;
	}
	asc_dvc->in_critical_cnt++;
	if ((scsiq->q1.cntl & QC_SG_HEAD) != 0) {
		if ((sg_entry_cnt = sg_head->entry_cnt) == 0) {
			asc_dvc->in_critical_cnt--;
			return ASC_ERROR;
		}
		if (sg_entry_cnt > ASC_MAX_SG_LIST) {
			asc_dvc->in_critical_cnt--;
			return ASC_ERROR;
		}
		if (sg_entry_cnt == 1) {
			scsiq->q1.data_addr = cpu_to_le32(sg_head->sg_list[0].addr);
			scsiq->q1.data_cnt = cpu_to_le32(sg_head->sg_list[0].bytes);
			scsiq->q1.cntl &= ~(QC_SG_HEAD | QC_SG_SWAP_QUEUE);
		}
		sg_entry_cnt_minus_one = sg_entry_cnt - 1;
	}
	scsi_cmd = scsiq->cdbptr[0];
	disable_syn_offset_one_fix = false;
	if ((asc_dvc->pci_fix_asyn_xfer & scsiq->q1.target_id) &&
	    !(asc_dvc->pci_fix_asyn_xfer_always & scsiq->q1.target_id)) {
		if (scsiq->q1.cntl & QC_SG_HEAD) {
			data_cnt = 0;
			for (i = 0; i < sg_entry_cnt; i++) {
				data_cnt += le32_to_cpu(sg_head->sg_list[i].
							bytes);
			}
		} else {
			data_cnt = le32_to_cpu(scsiq->q1.data_cnt);
		}
		if (data_cnt != 0UL) {
			if (data_cnt < 512UL) {
				disable_syn_offset_one_fix = true;
			} else {
				for (i = 0; i < ASC_SYN_OFFSET_ONE_DISABLE_LIST;
				     i++) {
					disable_cmd =
					    _syn_offset_one_disable_cmd[i];
					if (disable_cmd == 0xFF) {
						break;
					}
					if (scsi_cmd == disable_cmd) {
						disable_syn_offset_one_fix =
						    true;
						break;
					}
				}
			}
		}
	}
	if (disable_syn_offset_one_fix) {
		scsiq->q2.tag_code &= ~SIMPLE_QUEUE_TAG;
		scsiq->q2.tag_code |= (ASC_TAG_FLAG_DISABLE_ASYN_USE_SYN_FIX |
				       ASC_TAG_FLAG_DISABLE_DISCONNECT);
	} else {
		scsiq->q2.tag_code &= 0x27;
	}
	if ((scsiq->q1.cntl & QC_SG_HEAD) != 0) {
		if (asc_dvc->bug_fix_cntl) {
			if (asc_dvc->bug_fix_cntl & ASC_BUG_FIX_IF_NOT_DWB) {
				if ((scsi_cmd == READ_6) ||
				    (scsi_cmd == READ_10)) {
					addr = le32_to_cpu(sg_head->
								   sg_list
								   [sg_entry_cnt_minus_one].
								   addr) +
						le32_to_cpu(sg_head->
								  sg_list
								  [sg_entry_cnt_minus_one].
								  bytes);
					extra_bytes =
					    (uchar)((ushort)addr & 0x0003);
					if ((extra_bytes != 0)
					    &&
					    ((scsiq->q2.
					      tag_code &
					      ASC_TAG_FLAG_EXTRA_BYTES)
					     == 0)) {
						scsiq->q2.tag_code |=
						    ASC_TAG_FLAG_EXTRA_BYTES;
						scsiq->q1.extra_bytes =
						    extra_bytes;
						data_cnt =
						    le32_to_cpu(sg_head->
								sg_list
								[sg_entry_cnt_minus_one].
								bytes);
						data_cnt -= extra_bytes;
						sg_head->
						    sg_list
						    [sg_entry_cnt_minus_one].
						    bytes =
						    cpu_to_le32(data_cnt);
					}
				}
			}
		}
		sg_head->entry_to_copy = sg_head->entry_cnt;
		n_q_required = AscSgListToQueue(sg_entry_cnt);
		if ((AscGetNumOfFreeQueue(asc_dvc, target_ix, n_q_required) >=
		     (uint) n_q_required)
		    || ((scsiq->q1.cntl & QC_URGENT) != 0)) {
			if ((sta =
			     AscSendScsiQueue(asc_dvc, scsiq,
					      n_q_required)) == 1) {
				asc_dvc->in_critical_cnt--;
				return (sta);
			}
		}
	} else {
		if (asc_dvc->bug_fix_cntl) {
			if (asc_dvc->bug_fix_cntl & ASC_BUG_FIX_IF_NOT_DWB) {
				if ((scsi_cmd == READ_6) ||
				    (scsi_cmd == READ_10)) {
					addr =
					    le32_to_cpu(scsiq->q1.data_addr) +
					    le32_to_cpu(scsiq->q1.data_cnt);
					extra_bytes =
					    (uchar)((ushort)addr & 0x0003);
					if ((extra_bytes != 0)
					    &&
					    ((scsiq->q2.
					      tag_code &
					      ASC_TAG_FLAG_EXTRA_BYTES)
					     == 0)) {
						data_cnt =
						    le32_to_cpu(scsiq->q1.
								data_cnt);
						if (((ushort)data_cnt & 0x01FF)
						    == 0) {
							scsiq->q2.tag_code |=
							    ASC_TAG_FLAG_EXTRA_BYTES;
							data_cnt -= extra_bytes;
							scsiq->q1.data_cnt =
							    cpu_to_le32
							    (data_cnt);
							scsiq->q1.extra_bytes =
							    extra_bytes;
						}
					}
				}
			}
		}
		n_q_required = 1;
		if ((AscGetNumOfFreeQueue(asc_dvc, target_ix, 1) >= 1) ||
		    ((scsiq->q1.cntl & QC_URGENT) != 0)) {
			if ((sta = AscSendScsiQueue(asc_dvc, scsiq,
						    n_q_required)) == 1) {
				asc_dvc->in_critical_cnt--;
				return (sta);
			}
		}
	}
	asc_dvc->in_critical_cnt--;
	return (sta);
}