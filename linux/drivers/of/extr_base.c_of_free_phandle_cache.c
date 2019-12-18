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

/* Variables and functions */
 int /*<<< orphan*/  __of_free_phandle_cache () ; 
 int /*<<< orphan*/  devtree_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int of_free_phandle_cache(void)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&devtree_lock, flags);

	__of_free_phandle_cache();

	raw_spin_unlock_irqrestore(&devtree_lock, flags);

	return 0;
}