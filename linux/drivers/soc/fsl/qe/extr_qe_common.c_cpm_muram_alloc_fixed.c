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
struct genpool_data_fixed {scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ GENPOOL_OFFSET ; 
 unsigned long cpm_muram_alloc_common (unsigned long,int /*<<< orphan*/ ,struct genpool_data_fixed*) ; 
 int /*<<< orphan*/  cpm_muram_lock ; 
 int /*<<< orphan*/  gen_pool_fixed_alloc ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

unsigned long cpm_muram_alloc_fixed(unsigned long offset, unsigned long size)
{
	unsigned long start;
	unsigned long flags;
	struct genpool_data_fixed muram_pool_data_fixed;

	spin_lock_irqsave(&cpm_muram_lock, flags);
	muram_pool_data_fixed.offset = offset + GENPOOL_OFFSET;
	start = cpm_muram_alloc_common(size, gen_pool_fixed_alloc,
				       &muram_pool_data_fixed);
	spin_unlock_irqrestore(&cpm_muram_lock, flags);
	return start;
}