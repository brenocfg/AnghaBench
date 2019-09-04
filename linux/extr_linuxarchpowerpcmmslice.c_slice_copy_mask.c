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
struct slice_mask {int /*<<< orphan*/  high_slices; int /*<<< orphan*/  low_slices; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLICE_NUM_HIGH ; 
 int /*<<< orphan*/  bitmap_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void slice_copy_mask(struct slice_mask *dst,
					const struct slice_mask *src)
{
	dst->low_slices = src->low_slices;
	if (!SLICE_NUM_HIGH)
		return;
	bitmap_copy(dst->high_slices, src->high_slices, SLICE_NUM_HIGH);
}