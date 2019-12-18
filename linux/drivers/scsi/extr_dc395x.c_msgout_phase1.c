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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct ScsiReqBlk {int state; scalar_t__ msg_count; scalar_t__* msgout_buf; int /*<<< orphan*/  cmd; } ;
struct AdapterCtlBlk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  DC395x_write16 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_write8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_DATALATCH ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ MSG_ABORT ; 
 int /*<<< orphan*/  MSG_NOP ; 
 int /*<<< orphan*/  SCMD_FIFO_OUT ; 
 int SRB_ABORT_SENT ; 
 int SRB_MSGOUT ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_COMMAND ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_FIFO ; 
 int /*<<< orphan*/  clear_fifo (struct AdapterCtlBlk*,char*) ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msgout_phase1(struct AdapterCtlBlk *acb, struct ScsiReqBlk *srb,
		u16 *pscsi_status)
{
	u16 i;
	u8 *ptr;
	dprintkdbg(DBG_0, "msgout_phase1: (0x%p)\n", srb->cmd);

	clear_fifo(acb, "msgout_phase1");
	if (!(srb->state & SRB_MSGOUT)) {
		srb->state |= SRB_MSGOUT;
		dprintkl(KERN_DEBUG,
			"msgout_phase1: (0x%p) Phase unexpected\n",
			srb->cmd);	/* So what ? */
	}
	if (!srb->msg_count) {
		dprintkdbg(DBG_0, "msgout_phase1: (0x%p) NOP msg\n",
			srb->cmd);
		DC395x_write8(acb, TRM_S1040_SCSI_FIFO, MSG_NOP);
		DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);	/* it's important for atn stop */
		DC395x_write8(acb, TRM_S1040_SCSI_COMMAND, SCMD_FIFO_OUT);
		return;
	}
	ptr = (u8 *)srb->msgout_buf;
	for (i = 0; i < srb->msg_count; i++)
		DC395x_write8(acb, TRM_S1040_SCSI_FIFO, *ptr++);
	srb->msg_count = 0;
	if (srb->msgout_buf[0] == MSG_ABORT)
		srb->state = SRB_ABORT_SENT;

	DC395x_write8(acb, TRM_S1040_SCSI_COMMAND, SCMD_FIFO_OUT);
}