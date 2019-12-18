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
 int /*<<< orphan*/  DFS_POOL_STAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_lock ; 
 int /*<<< orphan*/  pool_reference ; 
 int /*<<< orphan*/  singleton_pool_references ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pool_register_ref(void)
{
	spin_lock_bh(&pool_lock);
	singleton_pool_references++;
	DFS_POOL_STAT_INC(pool_reference);
	spin_unlock_bh(&pool_lock);
}