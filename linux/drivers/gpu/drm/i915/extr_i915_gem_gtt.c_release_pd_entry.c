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
struct i915_page_table {int /*<<< orphan*/  used; } ;
struct i915_page_scratch {int dummy; } ;
struct i915_page_directory {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_pd_entry (struct i915_page_directory* const,unsigned short const,struct i915_page_scratch const* const) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
release_pd_entry(struct i915_page_directory * const pd,
		 const unsigned short idx,
		 struct i915_page_table * const pt,
		 const struct i915_page_scratch * const scratch)
{
	bool free = false;

	if (atomic_add_unless(&pt->used, -1, 1))
		return false;

	spin_lock(&pd->lock);
	if (atomic_dec_and_test(&pt->used)) {
		clear_pd_entry(pd, idx, scratch);
		free = true;
	}
	spin_unlock(&pd->lock);

	return free;
}