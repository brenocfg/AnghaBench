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
struct dm_integrity_range {scalar_t__ logical_sector; scalar_t__ n_sectors; } ;

/* Variables and functions */

__attribute__((used)) static bool ranges_overlap(struct dm_integrity_range *range1, struct dm_integrity_range *range2)
{
	return range1->logical_sector < range2->logical_sector + range2->n_sectors &&
	       range1->logical_sector + range1->n_sectors > range2->logical_sector;
}