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
struct i915_page_directory {struct i915_page_directory** entry; } ;

/* Variables and functions */

__attribute__((used)) static inline struct i915_page_directory *
i915_pd_entry(const struct i915_page_directory * const pdp,
	      const unsigned short n)
{
	return pdp->entry[n];
}