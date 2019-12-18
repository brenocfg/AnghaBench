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
struct cache_set {int /*<<< orphan*/  moving_in_flight; int /*<<< orphan*/  moving_gc_keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  bch_keybuf_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 

void bch_moving_init_cache_set(struct cache_set *c)
{
	bch_keybuf_init(&c->moving_gc_keys);
	sema_init(&c->moving_in_flight, 64);
}