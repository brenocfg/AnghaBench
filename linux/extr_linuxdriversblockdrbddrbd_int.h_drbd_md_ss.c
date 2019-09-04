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
struct TYPE_2__ {int meta_dev_idx; } ;
struct drbd_backing_dev {TYPE_1__ md; int /*<<< orphan*/  backing_bdev; } ;
typedef  unsigned long long sector_t ;

/* Variables and functions */
 int const DRBD_MD_INDEX_FLEX_EXT ; 
 int const DRBD_MD_INDEX_FLEX_INT ; 
 int const DRBD_MD_INDEX_INTERNAL ; 
 unsigned long long MD_128MB_SECT ; 
 unsigned long long drbd_get_capacity (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline sector_t drbd_md_ss(struct drbd_backing_dev *bdev)
{
	const int meta_dev_idx = bdev->md.meta_dev_idx;

	if (meta_dev_idx == DRBD_MD_INDEX_FLEX_EXT)
		return 0;

	/* Since drbd08, internal meta data is always "flexible".
	 * position: last 4k aligned block of 4k size */
	if (meta_dev_idx == DRBD_MD_INDEX_INTERNAL ||
	    meta_dev_idx == DRBD_MD_INDEX_FLEX_INT)
		return (drbd_get_capacity(bdev->backing_bdev) & ~7ULL) - 8;

	/* external, some index; this is the old fixed size layout */
	return MD_128MB_SECT * bdev->md.meta_dev_idx;
}