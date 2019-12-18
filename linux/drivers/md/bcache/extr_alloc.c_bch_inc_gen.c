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
typedef  int /*<<< orphan*/  uint8_t ;
struct cache {TYPE_1__* set; } ;
struct bucket {int /*<<< orphan*/  gen; } ;
struct TYPE_2__ {scalar_t__ need_gc; } ;

/* Variables and functions */
 scalar_t__ BUCKET_GC_GEN_MAX ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  bucket_gc_gen (struct bucket*) ; 
 scalar_t__ max (scalar_t__,int /*<<< orphan*/ ) ; 

uint8_t bch_inc_gen(struct cache *ca, struct bucket *b)
{
	uint8_t ret = ++b->gen;

	ca->set->need_gc = max(ca->set->need_gc, bucket_gc_gen(b));
	WARN_ON_ONCE(ca->set->need_gc > BUCKET_GC_GEN_MAX);

	return ret;
}