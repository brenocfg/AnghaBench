#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int ushort ;
typedef  int uchar ;
struct TYPE_11__ {int init_sdtr; int sdtr_done; int max_sdtr_index; int use_tagged_qng; int /*<<< orphan*/ * sdtr_period_tbl; int /*<<< orphan*/  iop_base; } ;
struct TYPE_9__ {int target_id; scalar_t__ q_no; int /*<<< orphan*/  cntl; int /*<<< orphan*/  status; } ;
struct TYPE_8__ {int cdb_len; int /*<<< orphan*/  tag_code; int /*<<< orphan*/  target_ix; } ;
struct TYPE_10__ {TYPE_2__ q1; TYPE_1__ q2; scalar_t__ cdbptr; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  TYPE_3__ ASC_SCSI_Q ;
typedef  int /*<<< orphan*/  ASC_SCSIQ_2 ;
typedef  int /*<<< orphan*/  ASC_SCSIQ_1 ;
typedef  TYPE_4__ ASC_DVC_VAR ;

/* Variables and functions */
 int ASC_QNO_TO_QADDR (int) ; 
 scalar_t__ ASC_SCSIQ_B_STATUS ; 
 int ASC_SCSIQ_CDB_BEG ; 
 int ASC_SCSIQ_CPY_BEG ; 
 int ASC_SYN_MAX_OFFSET ; 
 int ASC_TIX_TO_TID (int /*<<< orphan*/ ) ; 
 int AscGetMCodeInitSDTRAtID (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscMemWordCopyPtrToLram (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  AscMsgOutSDTR (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscWriteLramWord (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DvcPutScsiQ (int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  QC_MSG_OUT ; 
 int /*<<< orphan*/  QS_FREE ; 
 scalar_t__ QS_READY ; 
 int /*<<< orphan*/  SIMPLE_QUEUE_TAG ; 

__attribute__((used)) static int AscPutReadyQueue(ASC_DVC_VAR *asc_dvc, ASC_SCSI_Q *scsiq, uchar q_no)
{
	ushort q_addr;
	uchar tid_no;
	uchar sdtr_data;
	uchar syn_period_ix;
	uchar syn_offset;
	PortAddr iop_base;

	iop_base = asc_dvc->iop_base;
	if (((asc_dvc->init_sdtr & scsiq->q1.target_id) != 0) &&
	    ((asc_dvc->sdtr_done & scsiq->q1.target_id) == 0)) {
		tid_no = ASC_TIX_TO_TID(scsiq->q2.target_ix);
		sdtr_data = AscGetMCodeInitSDTRAtID(iop_base, tid_no);
		syn_period_ix =
		    (sdtr_data >> 4) & (asc_dvc->max_sdtr_index - 1);
		syn_offset = sdtr_data & ASC_SYN_MAX_OFFSET;
		AscMsgOutSDTR(asc_dvc,
			      asc_dvc->sdtr_period_tbl[syn_period_ix],
			      syn_offset);
		scsiq->q1.cntl |= QC_MSG_OUT;
	}
	q_addr = ASC_QNO_TO_QADDR(q_no);
	if ((scsiq->q1.target_id & asc_dvc->use_tagged_qng) == 0) {
		scsiq->q2.tag_code &= ~SIMPLE_QUEUE_TAG;
	}
	scsiq->q1.status = QS_FREE;
	AscMemWordCopyPtrToLram(iop_base,
				q_addr + ASC_SCSIQ_CDB_BEG,
				(uchar *)scsiq->cdbptr, scsiq->q2.cdb_len >> 1);

	DvcPutScsiQ(iop_base,
		    q_addr + ASC_SCSIQ_CPY_BEG,
		    (uchar *)&scsiq->q1.cntl,
		    ((sizeof(ASC_SCSIQ_1) + sizeof(ASC_SCSIQ_2)) / 2) - 1);
	AscWriteLramWord(iop_base,
			 (ushort)(q_addr + (ushort)ASC_SCSIQ_B_STATUS),
			 (ushort)(((ushort)scsiq->q1.
				   q_no << 8) | (ushort)QS_READY));
	return 1;
}