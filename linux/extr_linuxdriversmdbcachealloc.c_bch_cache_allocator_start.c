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
struct task_struct {int dummy; } ;
struct cache {struct task_struct* alloc_thread; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  bch_allocator_thread ; 
 struct task_struct* kthread_run (int /*<<< orphan*/ ,struct cache*,char*) ; 

int bch_cache_allocator_start(struct cache *ca)
{
	struct task_struct *k = kthread_run(bch_allocator_thread,
					    ca, "bcache_allocator");
	if (IS_ERR(k))
		return PTR_ERR(k);

	ca->alloc_thread = k;
	return 0;
}