#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u16_le ;
struct scsi_cmnd {int result; int cmd_len; int /*<<< orphan*/ * cmnd; TYPE_2__* device; } ;
struct TYPE_12__ {int msgout_len; int trans_method; int /*<<< orphan*/  auto_paddr; TYPE_4__* cur_lunt; TYPE_3__* cur_target; scalar_t__* msgoutbuf; TYPE_6__* autoparam; } ;
typedef  TYPE_5__ nsp32_hw_data ;
struct TYPE_13__ {int target_id; void* sgt_pointer; void* transfer_control; void* command_control; int /*<<< orphan*/  sample_reg; int /*<<< orphan*/  ackwidth; int /*<<< orphan*/  syncreg; void* msgout; int /*<<< orphan*/ * cdb; } ;
typedef  TYPE_6__ nsp32_autoparam ;
struct TYPE_11__ {unsigned int sglun_paddr; } ;
struct TYPE_10__ {int /*<<< orphan*/  sample_reg; int /*<<< orphan*/  ackwidth; int /*<<< orphan*/  syncreg; } ;
struct TYPE_9__ {TYPE_1__* host; } ;
struct TYPE_8__ {unsigned int io_port; unsigned int this_id; scalar_t__ hostdata; } ;

/* Variables and functions */
 int ALL_COUNTER_CLR ; 
 int AUTOSCSI_START ; 
 int AUTO_ATN ; 
 int AUTO_MSGIN_00_OR_04 ; 
 int AUTO_MSGIN_02 ; 
 int AUTO_PARAMETER ; 
 int BIT (unsigned char) ; 
 int BM_START ; 
 unsigned char BUSMON_BUS_FREE ; 
 unsigned char BUSMON_PHASE_MASK ; 
 int CB_IO_MODE ; 
 int CB_MMIO_MODE ; 
 int CLEAR_CDB_FIFO_POINTER ; 
 int /*<<< orphan*/  COMMAND_CONTROL ; 
 int DID_BUS_BUSY ; 
 int DID_ERROR ; 
 int FALSE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 unsigned int MV_VALID ; 
 int /*<<< orphan*/  NSP32_DEBUG_AUTOSCSI ; 
#define  NSP32_TRANSFER_BUSMASTER 130 
#define  NSP32_TRANSFER_MMIO 129 
#define  NSP32_TRANSFER_PIO 128 
 int /*<<< orphan*/  SCSI_BUS_MONITOR ; 
 int /*<<< orphan*/  SGT_ADR ; 
 int TRANSFER_GO ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int nsp32_arbitration (struct scsi_cmnd*,unsigned int) ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nsp32_msg (int /*<<< orphan*/ ,char*) ; 
 unsigned char nsp32_read1 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_write2 (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nsp32_write4 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char scmd_id (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  show_busphase (unsigned char) ; 

__attribute__((used)) static int nsp32_selection_autopara(struct scsi_cmnd *SCpnt)
{
	nsp32_hw_data  *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	unsigned int	base    = SCpnt->device->host->io_port;
	unsigned int	host_id = SCpnt->device->host->this_id;
	unsigned char	target  = scmd_id(SCpnt);
	nsp32_autoparam *param  = data->autoparam;
	unsigned char	phase;
	int		i, ret;
	unsigned int	msgout;
	u16_le	        s;

	nsp32_dbg(NSP32_DEBUG_AUTOSCSI, "in");

	/*
	 * check bus free
	 */
	phase = nsp32_read1(base, SCSI_BUS_MONITOR);
	if (phase != BUSMON_BUS_FREE) {
		nsp32_msg(KERN_WARNING, "bus busy");
		show_busphase(phase & BUSMON_PHASE_MASK);
		SCpnt->result = DID_BUS_BUSY << 16;
		return FALSE;
	}

	/*
	 * message out
	 *
	 * Note: If the range of msgout_len is 1 - 3, fill scsi_msgout.
	 *       over 3 messages needs another routine.
	 */
	if (data->msgout_len == 0) {
		nsp32_msg(KERN_ERR, "SCSI MsgOut without any message!");
		SCpnt->result = DID_ERROR << 16;
		return FALSE;
	} else if (data->msgout_len > 0 && data->msgout_len <= 3) {
		msgout = 0;
		for (i = 0; i < data->msgout_len; i++) {
			/*
			 * the sending order of the message is:
			 *  MCNT 3: MSG#0 -> MSG#1 -> MSG#2
			 *  MCNT 2:          MSG#1 -> MSG#2
			 *  MCNT 1:                   MSG#2    
			 */
			msgout >>= 8;
			msgout |= ((unsigned int)(data->msgoutbuf[i]) << 24);
		}
		msgout |= MV_VALID;	/* MV valid */
		msgout |= (unsigned int)data->msgout_len; /* len */
	} else {
		/* data->msgout_len > 3 */
		msgout = 0;
	}

	// nsp_dbg(NSP32_DEBUG_AUTOSCSI, "sel time out=0x%x\n", nsp32_read2(base, SEL_TIME_OUT));
	// nsp32_write2(base, SEL_TIME_OUT,   SEL_TIMEOUT_TIME);

	/*
	 * setup asic parameter
	 */
	memset(param, 0, sizeof(nsp32_autoparam));

	/* cdb */
	for (i = 0; i < SCpnt->cmd_len; i++) {
		param->cdb[4 * i] = SCpnt->cmnd[i];
	}

	/* outgoing messages */
	param->msgout = cpu_to_le32(msgout);

	/* syncreg, ackwidth, target id, SREQ sampling rate */
	param->syncreg    = data->cur_target->syncreg;
	param->ackwidth   = data->cur_target->ackwidth;
	param->target_id  = BIT(host_id) | BIT(target);
	param->sample_reg = data->cur_target->sample_reg;

	// nsp32_dbg(NSP32_DEBUG_AUTOSCSI, "sample rate=0x%x\n", data->cur_target->sample_reg);

	/* command control */
	param->command_control = cpu_to_le16(CLEAR_CDB_FIFO_POINTER |
					     AUTOSCSI_START         |
					     AUTO_MSGIN_00_OR_04    |
					     AUTO_MSGIN_02          |
					     AUTO_ATN               );


	/* transfer control */
	s = 0;
	switch (data->trans_method) {
	case NSP32_TRANSFER_BUSMASTER:
		s |= BM_START;
		break;
	case NSP32_TRANSFER_MMIO:
		s |= CB_MMIO_MODE;
		break;
	case NSP32_TRANSFER_PIO:
		s |= CB_IO_MODE;
		break;
	default:
		nsp32_msg(KERN_ERR, "unknown trans_method");
		break;
	}
	/*
	 * OR-ed BLIEND_MODE, FIFO intr is decreased, instead of PCI bus waits.
	 * For bus master transfer, it's taken off.
	 */
	s |= (TRANSFER_GO | ALL_COUNTER_CLR);
	param->transfer_control = cpu_to_le16(s);

	/* sg table addr */
	param->sgt_pointer = cpu_to_le32(data->cur_lunt->sglun_paddr);

	/*
	 * transfer parameter to ASIC
	 */
	nsp32_write4(base, SGT_ADR,         data->auto_paddr);
	nsp32_write2(base, COMMAND_CONTROL, CLEAR_CDB_FIFO_POINTER |
		                            AUTO_PARAMETER         );

	/*
	 * Check arbitration
	 */
	ret = nsp32_arbitration(SCpnt, base);

	return ret;
}