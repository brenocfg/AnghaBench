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
struct scsi_device {scalar_t__ scsi_level; scalar_t__ try_rc_10_first; TYPE_1__* host; } ;
struct TYPE_2__ {int max_cmd_len; } ;

/* Variables and functions */
 scalar_t__ SCSI_SPC_2 ; 
 scalar_t__ scsi_device_protection (struct scsi_device*) ; 

__attribute__((used)) static int sd_try_rc16_first(struct scsi_device *sdp)
{
	if (sdp->host->max_cmd_len < 16)
		return 0;
	if (sdp->try_rc_10_first)
		return 0;
	if (sdp->scsi_level > SCSI_SPC_2)
		return 1;
	if (scsi_device_protection(sdp))
		return 1;
	return 0;
}