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
struct cache_set {int /*<<< orphan*/  gc_thread; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_gc_thread ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct cache_set*,char*) ; 

int bch_gc_thread_start(struct cache_set *c)
{
	c->gc_thread = kthread_run(bch_gc_thread, c, "bcache_gc");
	return PTR_ERR_OR_ZERO(c->gc_thread);
}