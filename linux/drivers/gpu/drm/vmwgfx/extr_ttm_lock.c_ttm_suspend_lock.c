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
struct ttm_lock {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ttm_suspend_lock (struct ttm_lock*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ttm_suspend_lock(struct ttm_lock *lock)
{
	wait_event(lock->queue, __ttm_suspend_lock(lock));
}