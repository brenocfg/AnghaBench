#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ACK_WIDTH ; 
 int /*<<< orphan*/  ARBIT_STATUS ; 
 int /*<<< orphan*/  BM_CNT ; 
 int /*<<< orphan*/  BM_START_ADR ; 
 int /*<<< orphan*/  COMMAND_CONTROL ; 
 int /*<<< orphan*/  FIFO_REST_CNT ; 
 int /*<<< orphan*/  IRQ_STATUS ; 
 int /*<<< orphan*/  MISC_WR ; 
 int NSP32_DEBUG_MASK ; 
 int NSP32_SPECIAL_PRINT_REGISTER ; 
 int /*<<< orphan*/  OLD_SCSI_PHASE ; 
 int /*<<< orphan*/  SACK_CNT ; 
 int /*<<< orphan*/  SAVED_SACK_CNT ; 
 int /*<<< orphan*/  SCSI_BUS_CONTROL ; 
 int /*<<< orphan*/  SCSI_BUS_MONITOR ; 
 int /*<<< orphan*/  SCSI_CSB_IN ; 
 int /*<<< orphan*/  SCSI_EXECUTE_PHASE ; 
 int /*<<< orphan*/  SCSI_MSG_OUT ; 
 int /*<<< orphan*/  SCSI_OUT_LATCH_TARGET_ID ; 
 int /*<<< orphan*/  SEL_TIME_OUT ; 
 int /*<<< orphan*/  SGT_ADR ; 
 int /*<<< orphan*/  SREQ_CNT ; 
 int /*<<< orphan*/  SREQ_SMPL_RATE ; 
 int /*<<< orphan*/  SYNC_REG ; 
 int /*<<< orphan*/  TRANSFER_STATUS ; 
 int /*<<< orphan*/  nsp32_index_read1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_index_read2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_read1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_read2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_read4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void nsp32_print_register(int base)
{
	if (!(NSP32_DEBUG_MASK & NSP32_SPECIAL_PRINT_REGISTER))
		return;

	printk("Phase=0x%x, ", nsp32_read1(base, SCSI_BUS_MONITOR));
	printk("OldPhase=0x%x, ", nsp32_index_read1(base, OLD_SCSI_PHASE));
	printk("syncreg=0x%x, ", nsp32_read1(base, SYNC_REG));
	printk("ackwidth=0x%x, ", nsp32_read1(base, ACK_WIDTH));
	printk("sgtpaddr=0x%lx, ", nsp32_read4(base, SGT_ADR));
	printk("scsioutlatch=0x%x, ", nsp32_read1(base, SCSI_OUT_LATCH_TARGET_ID));
	printk("msgout=0x%lx, ", nsp32_read4(base, SCSI_MSG_OUT));
	printk("miscrd=0x%x, ", nsp32_index_read2(base, MISC_WR));
	printk("seltimeout=0x%x, ", nsp32_read2(base, SEL_TIME_OUT));
	printk("sreqrate=0x%x, ", nsp32_read1(base, SREQ_SMPL_RATE));
	printk("transStatus=0x%x, ", nsp32_read2(base, TRANSFER_STATUS));
	printk("reselectid=0x%x, ", nsp32_read2(base, COMMAND_CONTROL));
	printk("arbit=0x%x, ", nsp32_read1(base, ARBIT_STATUS));
	printk("BmStart=0x%lx, ", nsp32_read4(base, BM_START_ADR));
	printk("BmCount=0x%lx, ", nsp32_read4(base, BM_CNT));
	printk("SackCnt=0x%lx, ", nsp32_read4(base, SACK_CNT));
	printk("SReqCnt=0x%lx, ", nsp32_read4(base, SREQ_CNT));
	printk("SavedSackCnt=0x%lx, ", nsp32_read4(base, SAVED_SACK_CNT));
	printk("ScsiBusControl=0x%x, ", nsp32_read1(base, SCSI_BUS_CONTROL));
	printk("FifoRestCnt=0x%x, ", nsp32_read2(base, FIFO_REST_CNT));
	printk("CdbIn=0x%x, ", nsp32_read1(base, SCSI_CSB_IN));
	printk("\n");

	if (0) {
		printk("execph=0x%x, ", nsp32_read2(base, SCSI_EXECUTE_PHASE));
		printk("IrqStatus=0x%x, ", nsp32_read2(base, IRQ_STATUS));
		printk("\n");
	}
}