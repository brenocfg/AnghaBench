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
typedef  scalar_t__ u64 ;
struct drm_mm_scan {unsigned long color; int mode; scalar_t__ hit_end; int /*<<< orphan*/  hit_start; scalar_t__ range_end; scalar_t__ range_start; scalar_t__ size; scalar_t__ remainder_mask; scalar_t__ alignment; struct drm_mm* mm; } ;
struct drm_mm {int scan_active; } ;
typedef  enum drm_mm_insert_mode { ____Placeholder_drm_mm_insert_mode } drm_mm_insert_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MM_BUG_ON (int) ; 
 int /*<<< orphan*/  U64_MAX ; 
 scalar_t__ is_power_of_2 (scalar_t__) ; 

void drm_mm_scan_init_with_range(struct drm_mm_scan *scan,
				 struct drm_mm *mm,
				 u64 size,
				 u64 alignment,
				 unsigned long color,
				 u64 start,
				 u64 end,
				 enum drm_mm_insert_mode mode)
{
	DRM_MM_BUG_ON(start >= end);
	DRM_MM_BUG_ON(!size || size > end - start);
	DRM_MM_BUG_ON(mm->scan_active);

	scan->mm = mm;

	if (alignment <= 1)
		alignment = 0;

	scan->color = color;
	scan->alignment = alignment;
	scan->remainder_mask = is_power_of_2(alignment) ? alignment - 1 : 0;
	scan->size = size;
	scan->mode = mode;

	DRM_MM_BUG_ON(end <= start);
	scan->range_start = start;
	scan->range_end = end;

	scan->hit_start = U64_MAX;
	scan->hit_end = 0;
}