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
struct intel_timeline {int /*<<< orphan*/  hwsp_ggtt; int /*<<< orphan*/  hwsp_cacheline; int /*<<< orphan*/  pin_count; scalar_t__ hwsp_offset; } ;

/* Variables and functions */
 int PIN_GLOBAL ; 
 int PIN_HIGH ; 
 int /*<<< orphan*/  __i915_vma_unpin (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_fetch_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cacheline_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cacheline_release (int /*<<< orphan*/ ) ; 
 scalar_t__ i915_ggtt_offset (int /*<<< orphan*/ ) ; 
 int i915_vma_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ offset_in_page (scalar_t__) ; 

int intel_timeline_pin(struct intel_timeline *tl)
{
	int err;

	if (atomic_add_unless(&tl->pin_count, 1, 0))
		return 0;

	err = i915_vma_pin(tl->hwsp_ggtt, 0, 0, PIN_GLOBAL | PIN_HIGH);
	if (err)
		return err;

	tl->hwsp_offset =
		i915_ggtt_offset(tl->hwsp_ggtt) +
		offset_in_page(tl->hwsp_offset);

	cacheline_acquire(tl->hwsp_cacheline);
	if (atomic_fetch_inc(&tl->pin_count)) {
		cacheline_release(tl->hwsp_cacheline);
		__i915_vma_unpin(tl->hwsp_ggtt);
	}

	return 0;
}