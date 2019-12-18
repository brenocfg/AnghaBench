#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* device; } ;
typedef  int /*<<< orphan*/  nsp32_sgtable ;
struct TYPE_10__ {int msgout_len; int /*<<< orphan*/ * msgoutbuf; TYPE_3__* cur_lunt; } ;
typedef  TYPE_4__ nsp32_hw_data ;
struct TYPE_9__ {int sglun_paddr; int cur_entry; } ;
struct TYPE_8__ {TYPE_1__* host; } ;
struct TYPE_7__ {unsigned int io_port; scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT ; 
 int AUTOSCSI_RESTART ; 
 int AUTO_COMMAND_PHASE ; 
 int AUTO_MSGIN_00_OR_04 ; 
 int AUTO_MSGIN_02 ; 
 int CLEAR_CDB_FIFO_POINTER ; 
 int /*<<< orphan*/  COMMAND_CONTROL ; 
 int /*<<< orphan*/  NEGATE ; 
 int /*<<< orphan*/  NSP32_DEBUG_MSGOUTOCCUR ; 
 int /*<<< orphan*/  SCSI_BUS_MONITOR ; 
 int /*<<< orphan*/  SCSI_DATA_WITH_ACK ; 
 int /*<<< orphan*/  nsp32_build_nop (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  nsp32_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  nsp32_read1 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_wait_req (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_wait_sack (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_write1 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_write2 (unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nsp32_msgout_occur(struct scsi_cmnd *SCpnt)
{
	nsp32_hw_data *data = (nsp32_hw_data *)SCpnt->device->host->hostdata;
	unsigned int base   = SCpnt->device->host->io_port;
	//unsigned short command;
	long new_sgtp;
	int i;
	
	nsp32_dbg(NSP32_DEBUG_MSGOUTOCCUR,
		  "enter: msgout_len: 0x%x", data->msgout_len);

	/*
	 * If MsgOut phase is occurred without having any
	 * message, then No_Operation is sent (SCSI-2).
	 */
	if (data->msgout_len == 0) {
		nsp32_build_nop(SCpnt);
	}

	/*
	 * Set SGTP ADDR current entry for restarting AUTOSCSI, 
	 * because SGTP is incremented next point.
	 * There is few statement in the specification...
	 */
 	new_sgtp = data->cur_lunt->sglun_paddr + 
		   (data->cur_lunt->cur_entry * sizeof(nsp32_sgtable));

	/*
	 * send messages
	 */
	for (i = 0; i < data->msgout_len; i++) {
		nsp32_dbg(NSP32_DEBUG_MSGOUTOCCUR,
			  "%d : 0x%x", i, data->msgoutbuf[i]);

		/*
		 * Check REQ is asserted.
		 */
		nsp32_wait_req(data, ASSERT);

		if (i == (data->msgout_len - 1)) {
			/*
			 * If the last message, set the AutoSCSI restart
			 * before send back the ack message. AutoSCSI
			 * restart automatically negate ATN signal.
			 */
			//command = (AUTO_MSGIN_00_OR_04 | AUTO_MSGIN_02);
			//nsp32_restart_autoscsi(SCpnt, command);
			nsp32_write2(base, COMMAND_CONTROL,
					 (CLEAR_CDB_FIFO_POINTER |
					  AUTO_COMMAND_PHASE     |
					  AUTOSCSI_RESTART       |
					  AUTO_MSGIN_00_OR_04    |
					  AUTO_MSGIN_02          ));
		}
		/*
		 * Write data with SACK, then wait sack is
		 * automatically negated.
		 */
		nsp32_write1(base, SCSI_DATA_WITH_ACK, data->msgoutbuf[i]);
		nsp32_wait_sack(data, NEGATE);

		nsp32_dbg(NSP32_DEBUG_MSGOUTOCCUR, "bus: 0x%x\n",
			  nsp32_read1(base, SCSI_BUS_MONITOR));
	};

	data->msgout_len = 0;

	nsp32_dbg(NSP32_DEBUG_MSGOUTOCCUR, "exit");
}