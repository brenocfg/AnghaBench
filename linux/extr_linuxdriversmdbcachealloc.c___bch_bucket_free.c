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
struct bucket {int dummy; } ;
struct TYPE_2__ {scalar_t__ avail_nbuckets; scalar_t__ nbuckets; int /*<<< orphan*/  gc_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_GC_MARK (struct bucket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_GC_SECTORS_USED (struct bucket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_update_bucket_in_use (TYPE_1__*,int /*<<< orphan*/ *) ; 

void __bch_bucket_free(struct cache *ca, struct bucket *b)
{
	SET_GC_MARK(b, 0);
	SET_GC_SECTORS_USED(b, 0);

	if (ca->set->avail_nbuckets < ca->set->nbuckets) {
		ca->set->avail_nbuckets++;
		bch_update_bucket_in_use(ca->set, &ca->set->gc_stats);
	}
}