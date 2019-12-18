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
struct stripe_head {int /*<<< orphan*/  ppl_page; struct r5dev* dev; int /*<<< orphan*/  log_start; struct r5conf* raid_conf; int /*<<< orphan*/  count; int /*<<< orphan*/  log_list; int /*<<< orphan*/  r5c; int /*<<< orphan*/  lru; int /*<<< orphan*/  batch_list; int /*<<< orphan*/  batch_lock; int /*<<< orphan*/  stripe_lock; } ;
struct r5dev {int /*<<< orphan*/  rvec; int /*<<< orphan*/  rreq; int /*<<< orphan*/  vec; int /*<<< orphan*/  req; } ;
struct r5conf {int dummy; } ;
struct kmem_cache {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MaxSector ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bio_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_stripe (struct kmem_cache*,struct stripe_head*) ; 
 struct stripe_head* kmem_cache_zalloc (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 scalar_t__ raid5_has_ppl (struct r5conf*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct stripe_head *alloc_stripe(struct kmem_cache *sc, gfp_t gfp,
	int disks, struct r5conf *conf)
{
	struct stripe_head *sh;
	int i;

	sh = kmem_cache_zalloc(sc, gfp);
	if (sh) {
		spin_lock_init(&sh->stripe_lock);
		spin_lock_init(&sh->batch_lock);
		INIT_LIST_HEAD(&sh->batch_list);
		INIT_LIST_HEAD(&sh->lru);
		INIT_LIST_HEAD(&sh->r5c);
		INIT_LIST_HEAD(&sh->log_list);
		atomic_set(&sh->count, 1);
		sh->raid_conf = conf;
		sh->log_start = MaxSector;
		for (i = 0; i < disks; i++) {
			struct r5dev *dev = &sh->dev[i];

			bio_init(&dev->req, &dev->vec, 1);
			bio_init(&dev->rreq, &dev->rvec, 1);
		}

		if (raid5_has_ppl(conf)) {
			sh->ppl_page = alloc_page(gfp);
			if (!sh->ppl_page) {
				free_stripe(sc, sh);
				sh = NULL;
			}
		}
	}
	return sh;
}