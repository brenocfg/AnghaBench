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
typedef  int /*<<< orphan*/  u8 ;
struct scsi_cmnd {TYPE_2__* device; } ;
struct TYPE_6__ {int delay_time; } ;
struct AdapterCtlBlk {scalar_t__ acb_flag; int /*<<< orphan*/ * active_dcb; TYPE_3__ eeprom; scalar_t__ last_reset; int /*<<< orphan*/  waiting_timer; } ;
struct TYPE_5__ {scalar_t__ lun; int /*<<< orphan*/  id; TYPE_1__* host; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int CLRXFIFO ; 
 int /*<<< orphan*/  DC395x_read8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_write8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DID_RESET ; 
 int DMARESETMODULE ; 
 int DO_RSTMODULE ; 
 int HZ ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SUCCESS ; 
 int /*<<< orphan*/  TRM_S1040_DMA_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_DMA_INTEN ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_INTEN ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_INTSTATUS ; 
 int /*<<< orphan*/  clear_fifo (struct AdapterCtlBlk*,char*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  doing_srb_done (struct AdapterCtlBlk*,int /*<<< orphan*/ ,struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_cmnd*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  reset_dev_param (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  reset_scsi_bus (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  set_basic_config (struct AdapterCtlBlk*) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  waiting_process_next (struct AdapterCtlBlk*) ; 

__attribute__((used)) static int __dc395x_eh_bus_reset(struct scsi_cmnd *cmd)
{
	struct AdapterCtlBlk *acb =
		(struct AdapterCtlBlk *)cmd->device->host->hostdata;
	dprintkl(KERN_INFO,
		"eh_bus_reset: (0%p) target=<%02i-%i> cmd=%p\n",
		cmd, cmd->device->id, (u8)cmd->device->lun, cmd);

	if (timer_pending(&acb->waiting_timer))
		del_timer(&acb->waiting_timer);

	/*
	 * disable interrupt    
	 */
	DC395x_write8(acb, TRM_S1040_DMA_INTEN, 0x00);
	DC395x_write8(acb, TRM_S1040_SCSI_INTEN, 0x00);
	DC395x_write8(acb, TRM_S1040_SCSI_CONTROL, DO_RSTMODULE);
	DC395x_write8(acb, TRM_S1040_DMA_CONTROL, DMARESETMODULE);

	reset_scsi_bus(acb);
	udelay(500);

	/* We may be in serious trouble. Wait some seconds */
	acb->last_reset =
	    jiffies + 3 * HZ / 2 +
	    HZ * acb->eeprom.delay_time;

	/*
	 * re-enable interrupt      
	 */
	/* Clear SCSI FIFO          */
	DC395x_write8(acb, TRM_S1040_DMA_CONTROL, CLRXFIFO);
	clear_fifo(acb, "eh_bus_reset");
	/* Delete pending IRQ */
	DC395x_read8(acb, TRM_S1040_SCSI_INTSTATUS);
	set_basic_config(acb);

	reset_dev_param(acb);
	doing_srb_done(acb, DID_RESET, cmd, 0);
	acb->active_dcb = NULL;
	acb->acb_flag = 0;	/* RESET_DETECT, RESET_DONE ,RESET_DEV */
	waiting_process_next(acb);

	return SUCCESS;
}