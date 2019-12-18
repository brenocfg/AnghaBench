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
struct scsi_disk {int capacity; int zone_blocks; scalar_t__ nr_zones; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_NOTICE ; 
 int /*<<< orphan*/  sd_is_zoned (struct scsi_disk*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*,scalar_t__,int) ; 

void sd_zbc_print_zones(struct scsi_disk *sdkp)
{
	if (!sd_is_zoned(sdkp) || !sdkp->capacity)
		return;

	if (sdkp->capacity & (sdkp->zone_blocks - 1))
		sd_printk(KERN_NOTICE, sdkp,
			  "%u zones of %u logical blocks + 1 runt zone\n",
			  sdkp->nr_zones - 1,
			  sdkp->zone_blocks);
	else
		sd_printk(KERN_NOTICE, sdkp,
			  "%u zones of %u logical blocks\n",
			  sdkp->nr_zones,
			  sdkp->zone_blocks);
}