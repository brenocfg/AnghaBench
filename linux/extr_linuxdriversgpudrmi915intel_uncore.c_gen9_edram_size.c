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
typedef  unsigned int const u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int /*<<< orphan*/  edram_cap; } ;

/* Variables and functions */
 unsigned int const EDRAM_NUM_BANKS (int /*<<< orphan*/  const) ; 
 size_t EDRAM_SETS_IDX (int /*<<< orphan*/  const) ; 
 size_t EDRAM_WAYS_IDX (int /*<<< orphan*/  const) ; 

__attribute__((used)) static u64 gen9_edram_size(struct drm_i915_private *dev_priv)
{
	const unsigned int ways[8] = { 4, 8, 12, 16, 16, 16, 16, 16 };
	const unsigned int sets[4] = { 1, 1, 2, 2 };
	const u32 cap = dev_priv->edram_cap;

	return EDRAM_NUM_BANKS(cap) *
		ways[EDRAM_WAYS_IDX(cap)] *
		sets[EDRAM_SETS_IDX(cap)] *
		1024 * 1024;
}