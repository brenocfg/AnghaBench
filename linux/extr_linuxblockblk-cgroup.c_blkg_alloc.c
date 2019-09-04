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
struct request_queue {int /*<<< orphan*/  node; } ;
struct blkg_policy_data {int plid; struct blkcg_gq* blkg; } ;
struct blkcg_policy {struct blkg_policy_data* (* pd_alloc_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {struct blkcg_gq* blkg; } ;
struct blkcg_gq {struct blkg_policy_data** pd; TYPE_1__ rl; int /*<<< orphan*/  refcnt; struct blkcg* blkcg; int /*<<< orphan*/  q_node; struct request_queue* q; int /*<<< orphan*/  stat_ios; int /*<<< orphan*/  stat_bytes; } ;
struct blkcg {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int BLKCG_MAX_POLS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ blk_init_rl (TYPE_1__*,struct request_queue*,int /*<<< orphan*/ ) ; 
 struct blkcg_policy** blkcg_policy ; 
 int /*<<< orphan*/  blkcg_policy_enabled (struct request_queue*,struct blkcg_policy*) ; 
 struct blkcg blkcg_root ; 
 int /*<<< orphan*/  blkg_free (struct blkcg_gq*) ; 
 scalar_t__ blkg_rwstat_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct blkcg_gq* kzalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct blkg_policy_data* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct blkcg_gq *blkg_alloc(struct blkcg *blkcg, struct request_queue *q,
				   gfp_t gfp_mask)
{
	struct blkcg_gq *blkg;
	int i;

	/* alloc and init base part */
	blkg = kzalloc_node(sizeof(*blkg), gfp_mask, q->node);
	if (!blkg)
		return NULL;

	if (blkg_rwstat_init(&blkg->stat_bytes, gfp_mask) ||
	    blkg_rwstat_init(&blkg->stat_ios, gfp_mask))
		goto err_free;

	blkg->q = q;
	INIT_LIST_HEAD(&blkg->q_node);
	blkg->blkcg = blkcg;
	atomic_set(&blkg->refcnt, 1);

	/* root blkg uses @q->root_rl, init rl only for !root blkgs */
	if (blkcg != &blkcg_root) {
		if (blk_init_rl(&blkg->rl, q, gfp_mask))
			goto err_free;
		blkg->rl.blkg = blkg;
	}

	for (i = 0; i < BLKCG_MAX_POLS; i++) {
		struct blkcg_policy *pol = blkcg_policy[i];
		struct blkg_policy_data *pd;

		if (!blkcg_policy_enabled(q, pol))
			continue;

		/* alloc per-policy data and attach it to blkg */
		pd = pol->pd_alloc_fn(gfp_mask, q->node);
		if (!pd)
			goto err_free;

		blkg->pd[i] = pd;
		pd->blkg = blkg;
		pd->plid = i;
	}

	return blkg;

err_free:
	blkg_free(blkg);
	return NULL;
}