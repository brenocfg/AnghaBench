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
struct dm_integrity_c {unsigned int log2_metadata_run; unsigned int metadata_run; unsigned int log2_buffer_sectors; unsigned int log2_tag_size; unsigned int tag_size; TYPE_1__* sb; } ;
typedef  unsigned int sector_t ;
typedef  unsigned int __u64 ;
struct TYPE_2__ {unsigned int log2_interleave_sectors; } ;

/* Variables and functions */
 unsigned int SECTOR_SHIFT ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  sector_to_block (struct dm_integrity_c*,unsigned int) ; 

__attribute__((used)) static __u64 get_metadata_sector_and_offset(struct dm_integrity_c *ic, sector_t area,
					    sector_t offset, unsigned *metadata_offset)
{
	__u64 ms;
	unsigned mo;

	ms = area << ic->sb->log2_interleave_sectors;
	if (likely(ic->log2_metadata_run >= 0))
		ms += area << ic->log2_metadata_run;
	else
		ms += area * ic->metadata_run;
	ms >>= ic->log2_buffer_sectors;

	sector_to_block(ic, offset);

	if (likely(ic->log2_tag_size >= 0)) {
		ms += offset >> (SECTOR_SHIFT + ic->log2_buffer_sectors - ic->log2_tag_size);
		mo = (offset << ic->log2_tag_size) & ((1U << SECTOR_SHIFT << ic->log2_buffer_sectors) - 1);
	} else {
		ms += (__u64)offset * ic->tag_size >> (SECTOR_SHIFT + ic->log2_buffer_sectors);
		mo = (offset * ic->tag_size) & ((1U << SECTOR_SHIFT << ic->log2_buffer_sectors) - 1);
	}
	*metadata_offset = mo;
	return ms;
}