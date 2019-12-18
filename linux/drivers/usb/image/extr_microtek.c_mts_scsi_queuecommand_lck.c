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
struct scsi_cmnd {int result; int /*<<< orphan*/  cmd_len; int /*<<< orphan*/  cmnd; TYPE_2__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* final_callback ) (struct scsi_cmnd*) ;} ;
struct mts_desc {int /*<<< orphan*/  urb; TYPE_3__ context; int /*<<< orphan*/  ep_out; int /*<<< orphan*/  usb_dev; } ;
typedef  int /*<<< orphan*/  (* mts_scsi_cmnd_callback ) (struct scsi_cmnd*) ;
struct TYPE_5__ {scalar_t__ channel; scalar_t__ id; scalar_t__ lun; TYPE_1__* host; } ;
struct TYPE_4__ {scalar_t__* hostdata; } ;

/* Variables and functions */
 int DID_BAD_TARGET ; 
 int DID_ERROR ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  MTS_DEBUG (char*,...) ; 
 int /*<<< orphan*/  MTS_DEBUG_GOT_HERE () ; 
 int /*<<< orphan*/  MTS_ERROR (char*,int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mts_build_transfer_context (struct scsi_cmnd*,struct mts_desc*) ; 
 int /*<<< orphan*/  mts_command_done ; 
 int /*<<< orphan*/  mts_debug_dump (struct mts_desc*) ; 
 int /*<<< orphan*/  mts_show_command (struct scsi_cmnd*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mts_scsi_queuecommand_lck(struct scsi_cmnd *srb, mts_scsi_cmnd_callback callback)
{
	struct mts_desc* desc = (struct mts_desc*)(srb->device->host->hostdata[0]);
	int err = 0;
	int res;

	MTS_DEBUG_GOT_HERE();
	mts_show_command(srb);
	mts_debug_dump(desc);

	if ( srb->device->lun || srb->device->id || srb->device->channel ) {

		MTS_DEBUG("Command to LUN=%d ID=%d CHANNEL=%d from SCSI layer\n",(int)srb->device->lun,(int)srb->device->id, (int)srb->device->channel );

		MTS_DEBUG("this device doesn't exist\n");

		srb->result = DID_BAD_TARGET << 16;

		if(likely(callback != NULL))
			callback(srb);

		goto out;
	}

	
	usb_fill_bulk_urb(desc->urb,
		      desc->usb_dev,
		      usb_sndbulkpipe(desc->usb_dev,desc->ep_out),
		      srb->cmnd,
		      srb->cmd_len,
		      mts_command_done,
		      &desc->context
		      );


	mts_build_transfer_context( srb, desc );
	desc->context.final_callback = callback;
	
	/* here we need ATOMIC as we are called with the iolock */
	res=usb_submit_urb(desc->urb, GFP_ATOMIC);

	if(unlikely(res)){
		MTS_ERROR("error %d submitting URB\n",(int)res);
		srb->result = DID_ERROR << 16;

		if(likely(callback != NULL))
			callback(srb);

	}
out:
	return err;
}