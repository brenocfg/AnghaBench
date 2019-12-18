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
struct scsi_device {unsigned int channel; unsigned int id; TYPE_2__* host; } ;
struct myrs_hba {TYPE_1__* ctlr_info; } ;
struct TYPE_4__ {unsigned int max_id; } ;
struct TYPE_3__ {unsigned int physchan_present; } ;

/* Variables and functions */

__attribute__((used)) static unsigned short myrs_translate_ldev(struct myrs_hba *cs,
		struct scsi_device *sdev)
{
	unsigned short ldev_num;
	unsigned int chan_offset =
		sdev->channel - cs->ctlr_info->physchan_present;

	ldev_num = sdev->id + chan_offset * sdev->host->max_id;

	return ldev_num;
}