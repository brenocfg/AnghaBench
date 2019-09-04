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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_HASH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 

u64 __cmpxchg_u64(u64 *ptr, u64 old, u64 new)
{
	unsigned long flags;
	u64 prev;

	spin_lock_irqsave(ATOMIC_HASH(ptr), flags);
	if ((prev = *ptr) == old)
		*ptr = new;
	spin_unlock_irqrestore(ATOMIC_HASH(ptr), flags);

	return prev;
}