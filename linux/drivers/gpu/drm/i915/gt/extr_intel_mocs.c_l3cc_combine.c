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
typedef  int u16 ;
struct drm_i915_mocs_table {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 l3cc_combine(const struct drm_i915_mocs_table *table,
			       u16 low,
			       u16 high)
{
	return low | high << 16;
}