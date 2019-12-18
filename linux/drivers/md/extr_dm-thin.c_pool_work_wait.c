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
struct pool_work {int /*<<< orphan*/  complete; int /*<<< orphan*/  worker; } ;
struct pool {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK_ONSTACK (int /*<<< orphan*/ *,void (*) (struct work_struct*)) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pool_work_wait(struct pool_work *pw, struct pool *pool,
			   void (*fn)(struct work_struct *))
{
	INIT_WORK_ONSTACK(&pw->worker, fn);
	init_completion(&pw->complete);
	queue_work(pool->wq, &pw->worker);
	wait_for_completion(&pw->complete);
}