#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  phase; } ;
struct scsi_cmnd {TYPE_3__ SCp; TYPE_2__* device; } ;
struct TYPE_8__ {int SelectionTimeOut; } ;
typedef  TYPE_4__ nsp_hw_data ;
struct TYPE_6__ {TYPE_1__* host; } ;
struct TYPE_5__ {unsigned int this_id; unsigned int io_port; scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARBITSTATUS ; 
 unsigned char ARBIT_FAIL ; 
 int ARBIT_FLAG_CLEAR ; 
 int ARBIT_GO ; 
 unsigned char ARBIT_WIN ; 
 int BIT (unsigned char) ; 
 unsigned char BUSMON_BUS_FREE ; 
 int FALSE ; 
 int /*<<< orphan*/  PH_ARBSTART ; 
 int /*<<< orphan*/  PH_SELSTART ; 
 int /*<<< orphan*/  SCSIBUSCTRL ; 
 int /*<<< orphan*/  SCSIBUSMON ; 
 int /*<<< orphan*/  SCSIDATALATCH ; 
 int SCSI_ATN ; 
 int SCSI_BSY ; 
 int SCSI_DATAOUT_ENB ; 
 int SCSI_SEL ; 
 int /*<<< orphan*/  SETARBIT ; 
 int TRUE ; 
 unsigned char nsp_index_read (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp_index_write (unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nsp_start_timer (struct scsi_cmnd*,int) ; 
 unsigned char scmd_id (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int nsphw_start_selection(struct scsi_cmnd *SCpnt)
{
	unsigned int  host_id	 = SCpnt->device->host->this_id;
	unsigned int  base	 = SCpnt->device->host->io_port;
	unsigned char target	 = scmd_id(SCpnt);
	nsp_hw_data  *data = (nsp_hw_data *)SCpnt->device->host->hostdata;
	int	      time_out;
	unsigned char phase, arbit;

	//nsp_dbg(NSP_DEBUG_RESELECTION, "in");

	phase = nsp_index_read(base, SCSIBUSMON);
	if(phase != BUSMON_BUS_FREE) {
		//nsp_dbg(NSP_DEBUG_RESELECTION, "bus busy");
		return FALSE;
	}

	/* start arbitration */
	//nsp_dbg(NSP_DEBUG_RESELECTION, "start arbit");
	SCpnt->SCp.phase = PH_ARBSTART;
	nsp_index_write(base, SETARBIT, ARBIT_GO);

	time_out = 1000;
	do {
		/* XXX: what a stupid chip! */
		arbit = nsp_index_read(base, ARBITSTATUS);
		//nsp_dbg(NSP_DEBUG_RESELECTION, "arbit=%d, wait_count=%d", arbit, wait_count);
		udelay(1); /* hold 1.2us */
	} while((arbit & (ARBIT_WIN | ARBIT_FAIL)) == 0 &&
		(time_out-- != 0));

	if (!(arbit & ARBIT_WIN)) {
		//nsp_dbg(NSP_DEBUG_RESELECTION, "arbit fail");
		nsp_index_write(base, SETARBIT, ARBIT_FLAG_CLEAR);
		return FALSE;
	}

	/* assert select line */
	//nsp_dbg(NSP_DEBUG_RESELECTION, "assert SEL line");
	SCpnt->SCp.phase = PH_SELSTART;
	udelay(3); /* wait 2.4us */
	nsp_index_write(base, SCSIDATALATCH, BIT(host_id) | BIT(target));
	nsp_index_write(base, SCSIBUSCTRL,   SCSI_SEL | SCSI_BSY                    | SCSI_ATN);
	udelay(2); /* wait >1.2us */
	nsp_index_write(base, SCSIBUSCTRL,   SCSI_SEL | SCSI_BSY | SCSI_DATAOUT_ENB | SCSI_ATN);
	nsp_index_write(base, SETARBIT,	     ARBIT_FLAG_CLEAR);
	/*udelay(1);*/ /* wait >90ns */
	nsp_index_write(base, SCSIBUSCTRL,   SCSI_SEL            | SCSI_DATAOUT_ENB | SCSI_ATN);

	/* check selection timeout */
	nsp_start_timer(SCpnt, 1000/51);
	data->SelectionTimeOut = 1;

	return TRUE;
}