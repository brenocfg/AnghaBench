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
typedef  int /*<<< orphan*/  u64 ;
struct intel_ppat {int max_entries; int /*<<< orphan*/  dirty; TYPE_1__* entries; } ;
struct drm_i915_private {struct intel_ppat ppat; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN8_PPAT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEN8_PRIVATE_PAT_HI ; 
 int /*<<< orphan*/  GEN8_PRIVATE_PAT_LO ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bdw_private_pat_update_hw(struct drm_i915_private *dev_priv)
{
	struct intel_ppat *ppat = &dev_priv->ppat;
	u64 pat = 0;
	int i;

	for (i = 0; i < ppat->max_entries; i++)
		pat |= GEN8_PPAT(i, ppat->entries[i].value);

	bitmap_clear(ppat->dirty, 0, ppat->max_entries);

	I915_WRITE(GEN8_PRIVATE_PAT_LO, lower_32_bits(pat));
	I915_WRITE(GEN8_PRIVATE_PAT_HI, upper_32_bits(pat));
}