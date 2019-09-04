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
struct dm_integrity_c {TYPE_1__* sb; int /*<<< orphan*/  meta_dev; } ;
typedef  unsigned int sector_t ;
typedef  unsigned int __u8 ;
struct TYPE_2__ {unsigned int log2_interleave_sectors; } ;

/* Variables and functions */

__attribute__((used)) static void get_area_and_offset(struct dm_integrity_c *ic, sector_t data_sector,
				sector_t *area, sector_t *offset)
{
	if (!ic->meta_dev) {
		__u8 log2_interleave_sectors = ic->sb->log2_interleave_sectors;
		*area = data_sector >> log2_interleave_sectors;
		*offset = (unsigned)data_sector & ((1U << log2_interleave_sectors) - 1);
	} else {
		*area = 0;
		*offset = data_sector;
	}
}