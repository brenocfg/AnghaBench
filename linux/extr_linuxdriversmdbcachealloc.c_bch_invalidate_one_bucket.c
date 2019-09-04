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
struct cache {int buckets; int /*<<< orphan*/  free_inc; } ;
struct bucket {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bch_invalidate_one_bucket (struct cache*,struct bucket*) ; 
 int /*<<< orphan*/  fifo_push (int /*<<< orphan*/ *,struct bucket*) ; 

__attribute__((used)) static void bch_invalidate_one_bucket(struct cache *ca, struct bucket *b)
{
	__bch_invalidate_one_bucket(ca, b);

	fifo_push(&ca->free_inc, b - ca->buckets);
}