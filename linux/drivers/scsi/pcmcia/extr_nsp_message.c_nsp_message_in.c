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
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_6__ {unsigned char* MsgBuffer; int MsgLen; } ;
typedef  TYPE_3__ nsp_hw_data ;
struct TYPE_5__ {TYPE_1__* host; } ;
struct TYPE_4__ {unsigned int io_port; scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUSMON_REQ ; 
 int /*<<< orphan*/  BUSPHASE_MESSAGE_IN ; 
 int MSGBUF_SIZE ; 
 int /*<<< orphan*/  NSP_DEBUG_MSGINOCCUR ; 
 int /*<<< orphan*/  SCSIBUSCTRL ; 
 int /*<<< orphan*/  SCSIDATAIN ; 
 unsigned char SCSI_ACK ; 
 int /*<<< orphan*/  nsp_dbg (int /*<<< orphan*/ ,char*) ; 
 int nsp_expect_signal (struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char nsp_index_read (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp_index_write (unsigned int,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  nsp_negate_signal (struct scsi_cmnd*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void nsp_message_in(struct scsi_cmnd *SCpnt)
{
	unsigned int  base = SCpnt->device->host->io_port;
	nsp_hw_data  *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	unsigned char data_reg, control_reg;
	int           ret, len;

	/*
	 * XXX: NSP QUIRK
	 * NSP invoke interrupts only in the case of scsi phase changes,
	 * therefore we should poll the scsi phase here to catch 
	 * the next "msg in" if exists (no scsi phase changes).
	 */
	ret = 16;
	len = 0;

	nsp_dbg(NSP_DEBUG_MSGINOCCUR, "msgin loop");
	do {
		/* read data */
		data_reg = nsp_index_read(base, SCSIDATAIN);

		/* assert ACK */
		control_reg = nsp_index_read(base, SCSIBUSCTRL);
		control_reg |= SCSI_ACK;
		nsp_index_write(base, SCSIBUSCTRL, control_reg);
		nsp_negate_signal(SCpnt, BUSMON_REQ, "msgin<REQ>");

		data->MsgBuffer[len] = data_reg; len++;

		/* deassert ACK */
		control_reg =  nsp_index_read(base, SCSIBUSCTRL);
		control_reg &= ~SCSI_ACK;
		nsp_index_write(base, SCSIBUSCTRL, control_reg);

		/* catch a next signal */
		ret = nsp_expect_signal(SCpnt, BUSPHASE_MESSAGE_IN, BUSMON_REQ);
	} while (ret > 0 && MSGBUF_SIZE > len);

	data->MsgLen = len;

}