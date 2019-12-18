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
struct scsi_sense_hdr {int dummy; } ;
struct scsi_disk {TYPE_1__* disk; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/ * disk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_print_sense_hdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct scsi_sense_hdr*) ; 

__attribute__((used)) static void sd_print_sense_hdr(struct scsi_disk *sdkp,
			       struct scsi_sense_hdr *sshdr)
{
	scsi_print_sense_hdr(sdkp->device,
			     sdkp->disk ? sdkp->disk->disk_name : NULL, sshdr);
}