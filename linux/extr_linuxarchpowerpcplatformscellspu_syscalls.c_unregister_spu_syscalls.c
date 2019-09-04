#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spufs_calls {scalar_t__ owner; } ;
struct TYPE_3__ {scalar_t__ owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* spufs_calls ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void unregister_spu_syscalls(struct spufs_calls *calls)
{
	BUG_ON(spufs_calls->owner != calls->owner);
	RCU_INIT_POINTER(spufs_calls, NULL);
	synchronize_rcu();
}