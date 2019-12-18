#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct scsi_cmnd {int result; TYPE_2__* device; } ;
struct ScsiReqBlk {int /*<<< orphan*/  list; } ;
struct DeviceCtlBlk {int /*<<< orphan*/  srb_going_list; int /*<<< orphan*/  srb_waiting_list; } ;
struct AdapterCtlBlk {int /*<<< orphan*/  srb_free_list; } ;
struct TYPE_4__ {scalar_t__ lun; int /*<<< orphan*/  id; TYPE_1__* host; } ;
struct TYPE_3__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int FAILED ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int SUCCESS ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,...) ; 
 struct ScsiReqBlk* find_cmd (struct scsi_cmnd*,int /*<<< orphan*/ *) ; 
 struct DeviceCtlBlk* find_dcb (struct AdapterCtlBlk*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  free_tag (struct DeviceCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_unmap_srb (struct AdapterCtlBlk*,struct ScsiReqBlk*) ; 
 int /*<<< orphan*/  pci_unmap_srb_sense (struct AdapterCtlBlk*,struct ScsiReqBlk*) ; 

__attribute__((used)) static int dc395x_eh_abort(struct scsi_cmnd *cmd)
{
	/*
	 * Look into our command queues: If it has not been sent already,
	 * we remove it and return success. Otherwise fail.
	 */
	struct AdapterCtlBlk *acb =
	    (struct AdapterCtlBlk *)cmd->device->host->hostdata;
	struct DeviceCtlBlk *dcb;
	struct ScsiReqBlk *srb;
	dprintkl(KERN_INFO, "eh_abort: (0x%p) target=<%02i-%i> cmd=%p\n",
		cmd, cmd->device->id, (u8)cmd->device->lun, cmd);

	dcb = find_dcb(acb, cmd->device->id, cmd->device->lun);
	if (!dcb) {
		dprintkl(KERN_DEBUG, "eh_abort: No such device\n");
		return FAILED;
	}

	srb = find_cmd(cmd, &dcb->srb_waiting_list);
	if (srb) {
		list_del(&srb->list);
		pci_unmap_srb_sense(acb, srb);
		pci_unmap_srb(acb, srb);
		free_tag(dcb, srb);
		list_add_tail(&srb->list, &acb->srb_free_list);
		dprintkl(KERN_DEBUG, "eh_abort: Command was waiting\n");
		cmd->result = DID_ABORT << 16;
		return SUCCESS;
	}
	srb = find_cmd(cmd, &dcb->srb_going_list);
	if (srb) {
		dprintkl(KERN_DEBUG, "eh_abort: Command in progress\n");
		/* XXX: Should abort the command here */
	} else {
		dprintkl(KERN_DEBUG, "eh_abort: Command not found\n");
	}
	return FAILED;
}