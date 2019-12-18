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
struct intel_guc {int /*<<< orphan*/  ads_vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_VMA_RELEASE_MAP ; 
 int /*<<< orphan*/  i915_vma_unpin_and_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void intel_guc_ads_destroy(struct intel_guc *guc)
{
	i915_vma_unpin_and_release(&guc->ads_vma, I915_VMA_RELEASE_MAP);
}