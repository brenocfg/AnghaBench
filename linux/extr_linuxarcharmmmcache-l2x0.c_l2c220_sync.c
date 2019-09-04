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
 int /*<<< orphan*/  __l2c220_cache_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2x0_base ; 
 int /*<<< orphan*/  l2x0_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void l2c220_sync(void)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&l2x0_lock, flags);
	__l2c220_cache_sync(l2x0_base);
	raw_spin_unlock_irqrestore(&l2x0_lock, flags);
}