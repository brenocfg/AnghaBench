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
typedef  int u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTFIFOCTL ; 
 int GT_FIFO_FREE_ENTRIES_MASK ; 
 int __raw_i915_read32 (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 fifo_free_entries(struct drm_i915_private *dev_priv)
{
	u32 count = __raw_i915_read32(dev_priv, GTFIFOCTL);

	return count & GT_FIFO_FREE_ENTRIES_MASK;
}