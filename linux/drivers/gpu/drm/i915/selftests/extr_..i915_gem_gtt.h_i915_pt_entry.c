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
struct i915_page_table {int dummy; } ;
struct i915_page_directory {struct i915_page_table** entry; } ;

/* Variables and functions */

__attribute__((used)) static inline struct i915_page_table *
i915_pt_entry(const struct i915_page_directory * const pd,
	      const unsigned short n)
{
	return pd->entry[n];
}