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
struct scsi_cmnd {int result; int /*<<< orphan*/  sense_buffer; } ;
struct ata_device {int flags; } ;

/* Variables and functions */
 int ATA_DFLAG_D_SENSE ; 
 int DRIVER_SENSE ; 
 int SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  scsi_build_sense_buffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ata_scsi_set_sense(struct ata_device *dev, struct scsi_cmnd *cmd,
			u8 sk, u8 asc, u8 ascq)
{
	bool d_sense = (dev->flags & ATA_DFLAG_D_SENSE);

	if (!cmd)
		return;

	cmd->result = (DRIVER_SENSE << 24) | SAM_STAT_CHECK_CONDITION;

	scsi_build_sense_buffer(d_sense, cmd->sense_buffer, sk, asc, ascq);
}