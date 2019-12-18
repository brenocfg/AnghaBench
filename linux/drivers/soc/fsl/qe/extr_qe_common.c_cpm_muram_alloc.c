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
struct genpool_data_align {unsigned long align; } ;

/* Variables and functions */
 unsigned long cpm_muram_alloc_common (unsigned long,int /*<<< orphan*/ ,struct genpool_data_align*) ; 
 int /*<<< orphan*/  cpm_muram_lock ; 
 int /*<<< orphan*/  gen_pool_first_fit_align ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

unsigned long cpm_muram_alloc(unsigned long size, unsigned long align)
{
	unsigned long start;
	unsigned long flags;
	struct genpool_data_align muram_pool_data;

	spin_lock_irqsave(&cpm_muram_lock, flags);
	muram_pool_data.align = align;
	start = cpm_muram_alloc_common(size, gen_pool_first_fit_align,
				       &muram_pool_data);
	spin_unlock_irqrestore(&cpm_muram_lock, flags);
	return start;
}