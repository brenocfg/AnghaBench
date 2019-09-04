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
struct metadata_stats {int /*<<< orphan*/  era; int /*<<< orphan*/  snap; void* total; void* used; } ;
struct era_metadata {int /*<<< orphan*/  current_era; int /*<<< orphan*/  metadata_snap; int /*<<< orphan*/  sm; } ;
typedef  void* dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int) ; 
 int dm_sm_get_nr_blocks (int /*<<< orphan*/ ,void**) ; 
 int dm_sm_get_nr_free (int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static int metadata_get_stats(struct era_metadata *md, void *ptr)
{
	int r;
	struct metadata_stats *s = ptr;
	dm_block_t nr_free, nr_total;

	r = dm_sm_get_nr_free(md->sm, &nr_free);
	if (r) {
		DMERR("dm_sm_get_nr_free returned %d", r);
		return r;
	}

	r = dm_sm_get_nr_blocks(md->sm, &nr_total);
	if (r) {
		DMERR("dm_pool_get_metadata_dev_size returned %d", r);
		return r;
	}

	s->used = nr_total - nr_free;
	s->total = nr_total;
	s->snap = md->metadata_snap;
	s->era = md->current_era;

	return 0;
}