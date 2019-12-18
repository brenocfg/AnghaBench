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
struct dm_integrity_c {scalar_t__ journal_sections; scalar_t__ meta_device_sectors; scalar_t__ initial_sectors; int metadata_run; scalar_t__ tag_size; int log2_metadata_run; int provided_data_sectors; scalar_t__ start; int log2_buffer_sectors; TYPE_1__* sb; int /*<<< orphan*/  meta_dev; scalar_t__ journal_section_sectors; } ;
typedef  scalar_t__ sector_t ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {scalar_t__ log2_interleave_sectors; scalar_t__ log2_sectors_per_block; } ;

/* Variables and functions */
 int EINVAL ; 
 int METADATA_PADDING_SECTORS ; 
 scalar_t__ SB_SECTORS ; 
 int SECTOR_SHIFT ; 
 scalar_t__ UINT_MAX ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  calculate_journal_section_size (struct dm_integrity_c*) ; 
 int /*<<< orphan*/  get_area_and_offset (struct dm_integrity_c*,int,scalar_t__*,scalar_t__*) ; 
 scalar_t__ get_data_sector (struct dm_integrity_c*,scalar_t__,scalar_t__) ; 
 int roundup (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int calculate_device_limits(struct dm_integrity_c *ic)
{
	__u64 initial_sectors;

	calculate_journal_section_size(ic);
	initial_sectors = SB_SECTORS + (__u64)ic->journal_section_sectors * ic->journal_sections;
	if (initial_sectors + METADATA_PADDING_SECTORS >= ic->meta_device_sectors || initial_sectors > UINT_MAX)
		return -EINVAL;
	ic->initial_sectors = initial_sectors;

	if (!ic->meta_dev) {
		sector_t last_sector, last_area, last_offset;

		ic->metadata_run = roundup((__u64)ic->tag_size << (ic->sb->log2_interleave_sectors - ic->sb->log2_sectors_per_block),
					   (__u64)(1 << SECTOR_SHIFT << METADATA_PADDING_SECTORS)) >> SECTOR_SHIFT;
		if (!(ic->metadata_run & (ic->metadata_run - 1)))
			ic->log2_metadata_run = __ffs(ic->metadata_run);
		else
			ic->log2_metadata_run = -1;

		get_area_and_offset(ic, ic->provided_data_sectors - 1, &last_area, &last_offset);
		last_sector = get_data_sector(ic, last_area, last_offset);
		if (last_sector < ic->start || last_sector >= ic->meta_device_sectors)
			return -EINVAL;
	} else {
		__u64 meta_size = (ic->provided_data_sectors >> ic->sb->log2_sectors_per_block) * ic->tag_size;
		meta_size = (meta_size + ((1U << (ic->log2_buffer_sectors + SECTOR_SHIFT)) - 1))
				>> (ic->log2_buffer_sectors + SECTOR_SHIFT);
		meta_size <<= ic->log2_buffer_sectors;
		if (ic->initial_sectors + meta_size < ic->initial_sectors ||
		    ic->initial_sectors + meta_size > ic->meta_device_sectors)
			return -EINVAL;
		ic->metadata_run = 1;
		ic->log2_metadata_run = 0;
	}

	return 0;
}