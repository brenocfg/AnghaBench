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
struct cache_set {int /*<<< orphan*/  sectors_to_gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wake_up_gc (struct cache_set*) ; 

__attribute__((used)) static inline void force_wake_up_gc(struct cache_set *c)
{
	/*
	 * Garbage collection thread only works when sectors_to_gc < 0,
	 * calling wake_up_gc() won't start gc thread if sectors_to_gc is
	 * not a nagetive value.
	 * Therefore sectors_to_gc is set to -1 here, before waking up
	 * gc thread by calling wake_up_gc(). Then gc_should_run() will
	 * give a chance to permit gc thread to run. "Give a chance" means
	 * before going into gc_should_run(), there is still possibility
	 * that c->sectors_to_gc being set to other positive value. So
	 * this routine won't 100% make sure gc thread will be woken up
	 * to run.
	 */
	atomic_set(&c->sectors_to_gc, -1);
	wake_up_gc(c);
}