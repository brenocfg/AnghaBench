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
struct dmz_target {int /*<<< orphan*/  chunk_lock; int /*<<< orphan*/  chunk_wq; int /*<<< orphan*/  reclaim; int /*<<< orphan*/  chunk_rxtree; int /*<<< orphan*/  dev; } ;
struct dm_chunk_work {unsigned int chunk; int /*<<< orphan*/  work; int /*<<< orphan*/  bio_list; struct dmz_target* target; int /*<<< orphan*/  refcount; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_list_add (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  bio_list_init (int /*<<< orphan*/ *) ; 
 unsigned int dmz_bio_chunk (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  dmz_chunk_work ; 
 int /*<<< orphan*/  dmz_get_chunk_work (struct dm_chunk_work*) ; 
 int /*<<< orphan*/  dmz_reclaim_bio_acc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dm_chunk_work*) ; 
 struct dm_chunk_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,unsigned int,struct dm_chunk_work*) ; 
 struct dm_chunk_work* radix_tree_lookup (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int dmz_queue_chunk_work(struct dmz_target *dmz, struct bio *bio)
{
	unsigned int chunk = dmz_bio_chunk(dmz->dev, bio);
	struct dm_chunk_work *cw;
	int ret = 0;

	mutex_lock(&dmz->chunk_lock);

	/* Get the BIO chunk work. If one is not active yet, create one */
	cw = radix_tree_lookup(&dmz->chunk_rxtree, chunk);
	if (!cw) {

		/* Create a new chunk work */
		cw = kmalloc(sizeof(struct dm_chunk_work), GFP_NOIO);
		if (unlikely(!cw)) {
			ret = -ENOMEM;
			goto out;
		}

		INIT_WORK(&cw->work, dmz_chunk_work);
		refcount_set(&cw->refcount, 0);
		cw->target = dmz;
		cw->chunk = chunk;
		bio_list_init(&cw->bio_list);

		ret = radix_tree_insert(&dmz->chunk_rxtree, chunk, cw);
		if (unlikely(ret)) {
			kfree(cw);
			goto out;
		}
	}

	bio_list_add(&cw->bio_list, bio);
	dmz_get_chunk_work(cw);

	dmz_reclaim_bio_acc(dmz->reclaim);
	if (queue_work(dmz->chunk_wq, &cw->work))
		dmz_get_chunk_work(cw);
out:
	mutex_unlock(&dmz->chunk_lock);
	return ret;
}