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
struct TYPE_2__ {int meta_dev_idx; scalar_t__ md_size_sect; scalar_t__ md_offset; } ;
struct drbd_backing_dev {TYPE_1__ md; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
#define  DRBD_MD_INDEX_FLEX_EXT 130 
#define  DRBD_MD_INDEX_FLEX_INT 129 
#define  DRBD_MD_INDEX_INTERNAL 128 
 scalar_t__ MD_4kB_SECT ; 

__attribute__((used)) static inline sector_t drbd_md_last_sector(struct drbd_backing_dev *bdev)
{
	switch (bdev->md.meta_dev_idx) {
	case DRBD_MD_INDEX_INTERNAL:
	case DRBD_MD_INDEX_FLEX_INT:
		return bdev->md.md_offset + MD_4kB_SECT -1;
	case DRBD_MD_INDEX_FLEX_EXT:
	default:
		return bdev->md.md_offset + bdev->md.md_size_sect -1;
	}
}