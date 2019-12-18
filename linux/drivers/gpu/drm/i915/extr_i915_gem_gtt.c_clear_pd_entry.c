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
struct i915_page_scratch {int /*<<< orphan*/  encode; } ;
struct i915_page_directory {int /*<<< orphan*/ ** entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  px_base (struct i915_page_directory* const) ; 
 int /*<<< orphan*/  px_used (struct i915_page_directory* const) ; 
 int /*<<< orphan*/  write_dma_entry (int /*<<< orphan*/ ,unsigned short const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
clear_pd_entry(struct i915_page_directory * const pd,
	       const unsigned short idx,
	       const struct i915_page_scratch * const scratch)
{
	GEM_BUG_ON(atomic_read(px_used(pd)) == 0);

	write_dma_entry(px_base(pd), idx, scratch->encode);
	pd->entry[idx] = NULL;
	atomic_dec(px_used(pd));
}