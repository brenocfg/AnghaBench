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
 int __check_shared_memory (size_t) ; 
 int /*<<< orphan*/  shared_memory_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool check_shared_memory(size_t alloc_size)
{
	bool ret;

	spin_lock_irq(&shared_memory_lock);

	ret = __check_shared_memory(alloc_size);

	spin_unlock_irq(&shared_memory_lock);

	return ret;
}