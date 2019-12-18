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
struct scsi_device {scalar_t__ tagged_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  default_depth ; 
 int /*<<< orphan*/  scsi_change_queue_depth (struct scsi_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zfcp_scsi_slave_configure(struct scsi_device *sdp)
{
	if (sdp->tagged_supported)
		scsi_change_queue_depth(sdp, default_depth);
	return 0;
}