#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ScsiReqBlk {int cmd; int state; int /*<<< orphan*/  list; void* target_status; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  scsi_phase; } ;
struct DeviceCtlBlk {struct ScsiReqBlk* active_srb; int /*<<< orphan*/  srb_waiting_list; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; int /*<<< orphan*/  flag; } ;
struct TYPE_2__ {int delay_time; } ;
struct AdapterCtlBlk {scalar_t__ scan_devices; void* last_reset; struct DeviceCtlBlk* active_dcb; TYPE_1__ eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_DEV_ ; 
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  DBG_KG ; 
 scalar_t__ DC395x_MAX_RETRIES ; 
 int DC395x_read8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_write16 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DID_ABORT ; 
 int /*<<< orphan*/  DO_HWRESELECT ; 
 int HZ ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  PH_BUS_FREE ; 
 void* SCSI_STAT_SEL_TIMEOUT ; 
 int SRB_ABORT_SENT ; 
 int SRB_COMPLETED ; 
 int SRB_DISCONNECT ; 
 int SRB_FREE ; 
 int SRB_MSGOUT ; 
 int SRB_READY ; 
 int SRB_START_ ; 
 int SRB_UNEXPECT_RESEL ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_SIGNAL ; 
 int /*<<< orphan*/  clear_fifo (struct AdapterCtlBlk*,char*) ; 
 int /*<<< orphan*/  doing_srb_done (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_tag (struct DeviceCtlBlk*,struct ScsiReqBlk*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srb_done (struct AdapterCtlBlk*,struct DeviceCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  waiting_process_next (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  waiting_set_timer (struct AdapterCtlBlk*,int) ; 

__attribute__((used)) static void disconnect(struct AdapterCtlBlk *acb)
{
	struct DeviceCtlBlk *dcb = acb->active_dcb;
	struct ScsiReqBlk *srb;

	if (!dcb) {
		dprintkl(KERN_ERR, "disconnect: No such device\n");
		udelay(500);
		/* Suspend queue for a while */
		acb->last_reset =
		    jiffies + HZ / 2 +
		    HZ * acb->eeprom.delay_time;
		clear_fifo(acb, "disconnectEx");
		DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_HWRESELECT);
		return;
	}
	srb = dcb->active_srb;
	acb->active_dcb = NULL;
	dprintkdbg(DBG_0, "disconnect: (0x%p)\n", srb->cmd);

	srb->scsi_phase = PH_BUS_FREE;	/* initial phase */
	clear_fifo(acb, "disconnect");
	DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_HWRESELECT);
	if (srb->state & SRB_UNEXPECT_RESEL) {
		dprintkl(KERN_ERR,
			"disconnect: Unexpected reselection <%02i-%i>\n",
			dcb->target_id, dcb->target_lun);
		srb->state = 0;
		waiting_process_next(acb);
	} else if (srb->state & SRB_ABORT_SENT) {
		dcb->flag &= ~ABORT_DEV_;
		acb->last_reset = jiffies + HZ / 2 + 1;
		dprintkl(KERN_ERR, "disconnect: SRB_ABORT_SENT\n");
		doing_srb_done(acb, DID_ABORT, srb->cmd, 1);
		waiting_process_next(acb);
	} else {
		if ((srb->state & (SRB_START_ + SRB_MSGOUT))
		    || !(srb->
			 state & (SRB_DISCONNECT + SRB_COMPLETED))) {
			/*
			 * Selection time out 
			 * SRB_START_ || SRB_MSGOUT || (!SRB_DISCONNECT && !SRB_COMPLETED)
			 */
			/* Unexp. Disc / Sel Timeout */
			if (srb->state != SRB_START_
			    && srb->state != SRB_MSGOUT) {
				srb->state = SRB_READY;
				dprintkl(KERN_DEBUG,
					"disconnect: (0x%p) Unexpected\n",
					srb->cmd);
				srb->target_status = SCSI_STAT_SEL_TIMEOUT;
				goto disc1;
			} else {
				/* Normal selection timeout */
				dprintkdbg(DBG_KG, "disconnect: (0x%p) "
					"<%02i-%i> SelTO\n", srb->cmd,
					dcb->target_id, dcb->target_lun);
				if (srb->retry_count++ > DC395x_MAX_RETRIES
				    || acb->scan_devices) {
					srb->target_status =
					    SCSI_STAT_SEL_TIMEOUT;
					goto disc1;
				}
				free_tag(dcb, srb);
				list_move(&srb->list, &dcb->srb_waiting_list);
				dprintkdbg(DBG_KG,
					"disconnect: (0x%p) Retry\n",
					srb->cmd);
				waiting_set_timer(acb, HZ / 20);
			}
		} else if (srb->state & SRB_DISCONNECT) {
			u8 bval = DC395x_read8(acb, TRM_S1040_SCSI_SIGNAL);
			/*
			 * SRB_DISCONNECT (This is what we expect!)
			 */
			if (bval & 0x40) {
				dprintkdbg(DBG_0, "disconnect: SCSI bus stat "
					" 0x%02x: ACK set! Other controllers?\n",
					bval);
				/* It could come from another initiator, therefore don't do much ! */
			} else
				waiting_process_next(acb);
		} else if (srb->state & SRB_COMPLETED) {
		      disc1:
			/*
			 ** SRB_COMPLETED
			 */
			free_tag(dcb, srb);
			dcb->active_srb = NULL;
			srb->state = SRB_FREE;
			srb_done(acb, dcb, srb);
		}
	}
}