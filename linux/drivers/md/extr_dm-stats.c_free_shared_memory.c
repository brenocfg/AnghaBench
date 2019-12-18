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
 int /*<<< orphan*/  DMCRIT (char*) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 size_t shared_memory_amount ; 
 int /*<<< orphan*/  shared_memory_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_shared_memory(size_t alloc_size)
{
	unsigned long flags;

	spin_lock_irqsave(&shared_memory_lock, flags);

	if (WARN_ON_ONCE(shared_memory_amount < alloc_size)) {
		spin_unlock_irqrestore(&shared_memory_lock, flags);
		DMCRIT("Memory usage accounting bug.");
		return;
	}

	shared_memory_amount -= alloc_size;

	spin_unlock_irqrestore(&shared_memory_lock, flags);
}