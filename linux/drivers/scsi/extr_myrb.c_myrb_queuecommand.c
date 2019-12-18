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
struct scsi_device {scalar_t__ channel; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;struct scsi_device* device; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int DID_BAD_TARGET ; 
 int myrb_ldev_queuecommand (struct Scsi_Host*,struct scsi_cmnd*) ; 
 scalar_t__ myrb_logical_channel (struct Scsi_Host*) ; 
 int myrb_pthru_queuecommand (struct Scsi_Host*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static int myrb_queuecommand(struct Scsi_Host *shost,
		struct scsi_cmnd *scmd)
{
	struct scsi_device *sdev = scmd->device;

	if (sdev->channel > myrb_logical_channel(shost)) {
		scmd->result = (DID_BAD_TARGET << 16);
		scmd->scsi_done(scmd);
		return 0;
	}
	if (sdev->channel == myrb_logical_channel(shost))
		return myrb_ldev_queuecommand(shost, scmd);

	return myrb_pthru_queuecommand(shost, scmd);
}