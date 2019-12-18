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
struct scsi_cmnd {int /*<<< orphan*/  sense_buffer; } ;
struct myrb_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_SENSE ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  scsi_build_sense_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sg_copy_from_buffer (struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void myrb_request_sense(struct myrb_hba *cb,
		struct scsi_cmnd *scmd)
{
	scsi_build_sense_buffer(0, scmd->sense_buffer,
				NO_SENSE, 0, 0);
	scsi_sg_copy_from_buffer(scmd, scmd->sense_buffer,
				 SCSI_SENSE_BUFFERSIZE);
}