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
struct uas_dev_info {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct scsi_target {int no_report_luns; TYPE_1__ dev; } ;
struct TYPE_4__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int US_FL_NO_REPORT_LUNS ; 
 TYPE_2__* dev_to_shost (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uas_target_alloc(struct scsi_target *starget)
{
	struct uas_dev_info *devinfo = (struct uas_dev_info *)
			dev_to_shost(starget->dev.parent)->hostdata;

	if (devinfo->flags & US_FL_NO_REPORT_LUNS)
		starget->no_report_luns = 1;

	return 0;
}