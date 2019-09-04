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
struct ata_device {scalar_t__ class; } ;

/* Variables and functions */
 scalar_t__ ATA_DEV_ATA ; 
 unsigned long ATA_MASK_UDMA ; 

__attribute__((used)) static unsigned long serverworks_osb4_filter(struct ata_device *adev, unsigned long mask)
{
	if (adev->class == ATA_DEV_ATA)
		mask &= ~ATA_MASK_UDMA;
	return mask;
}