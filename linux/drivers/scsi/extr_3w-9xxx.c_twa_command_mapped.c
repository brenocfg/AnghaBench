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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 scalar_t__ TW_MIN_SGL_LENGTH ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int scsi_sg_count (struct scsi_cmnd*) ; 

__attribute__((used)) static bool twa_command_mapped(struct scsi_cmnd *cmd)
{
	return scsi_sg_count(cmd) != 1 ||
		scsi_bufflen(cmd) >= TW_MIN_SGL_LENGTH;
}