#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cache {TYPE_1__* set; } ;
struct bucket {int /*<<< orphan*/  pin; } ;
struct TYPE_2__ {int /*<<< orphan*/  gc_mark_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ GC_MARK (struct bucket*) ; 
 scalar_t__ GC_MARK_RECLAIMABLE ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ can_inc_bucket_gen (struct bucket*) ; 

bool bch_can_invalidate_bucket(struct cache *ca, struct bucket *b)
{
	BUG_ON(!ca->set->gc_mark_valid);

	return (!GC_MARK(b) ||
		GC_MARK(b) == GC_MARK_RECLAIMABLE) &&
		!atomic_read(&b->pin) &&
		can_inc_bucket_gen(b);
}