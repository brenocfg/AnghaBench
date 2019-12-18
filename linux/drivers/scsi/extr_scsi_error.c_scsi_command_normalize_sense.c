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
struct scsi_sense_hdr {int dummy; } ;
struct scsi_cmnd {int /*<<< orphan*/  sense_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int scsi_normalize_sense (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_sense_hdr*) ; 

bool scsi_command_normalize_sense(const struct scsi_cmnd *cmd,
				  struct scsi_sense_hdr *sshdr)
{
	return scsi_normalize_sense(cmd->sense_buffer,
			SCSI_SENSE_BUFFERSIZE, sshdr);
}