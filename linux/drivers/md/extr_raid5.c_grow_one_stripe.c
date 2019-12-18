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
struct stripe_head {int hash_lock_index; } ;
struct r5conf {int max_nr_stripes; int /*<<< orphan*/  active_stripes; int /*<<< orphan*/  slab_cache; int /*<<< orphan*/  pool_size; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int NR_STRIPE_HASH_LOCKS ; 
 struct stripe_head* alloc_stripe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct r5conf*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_stripe (int /*<<< orphan*/ ,struct stripe_head*) ; 
 scalar_t__ grow_buffers (struct stripe_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid5_release_stripe (struct stripe_head*) ; 
 int /*<<< orphan*/  shrink_buffers (struct stripe_head*) ; 

__attribute__((used)) static int grow_one_stripe(struct r5conf *conf, gfp_t gfp)
{
	struct stripe_head *sh;

	sh = alloc_stripe(conf->slab_cache, gfp, conf->pool_size, conf);
	if (!sh)
		return 0;

	if (grow_buffers(sh, gfp)) {
		shrink_buffers(sh);
		free_stripe(conf->slab_cache, sh);
		return 0;
	}
	sh->hash_lock_index =
		conf->max_nr_stripes % NR_STRIPE_HASH_LOCKS;
	/* we just created an active stripe so... */
	atomic_inc(&conf->active_stripes);

	raid5_release_stripe(sh);
	conf->max_nr_stripes++;
	return 1;
}