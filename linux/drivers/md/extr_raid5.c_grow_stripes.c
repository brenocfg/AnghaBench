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
struct stripe_head {int dummy; } ;
struct r5dev {int dummy; } ;
struct r5conf {char** cache_name; int level; size_t active_name; int pool_size; struct kmem_cache* slab_cache; TYPE_1__* mddev; int /*<<< orphan*/  previous_raid_disks; int /*<<< orphan*/  raid_disks; } ;
struct kmem_cache {int dummy; } ;
struct TYPE_2__ {scalar_t__ gendisk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  grow_one_stripe (struct r5conf*,int /*<<< orphan*/ ) ; 
 struct kmem_cache* kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* mdname (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static int grow_stripes(struct r5conf *conf, int num)
{
	struct kmem_cache *sc;
	size_t namelen = sizeof(conf->cache_name[0]);
	int devs = max(conf->raid_disks, conf->previous_raid_disks);

	if (conf->mddev->gendisk)
		snprintf(conf->cache_name[0], namelen,
			"raid%d-%s", conf->level, mdname(conf->mddev));
	else
		snprintf(conf->cache_name[0], namelen,
			"raid%d-%p", conf->level, conf->mddev);
	snprintf(conf->cache_name[1], namelen, "%.27s-alt", conf->cache_name[0]);

	conf->active_name = 0;
	sc = kmem_cache_create(conf->cache_name[conf->active_name],
			       sizeof(struct stripe_head)+(devs-1)*sizeof(struct r5dev),
			       0, 0, NULL);
	if (!sc)
		return 1;
	conf->slab_cache = sc;
	conf->pool_size = devs;
	while (num--)
		if (!grow_one_stripe(conf, GFP_KERNEL))
			return 1;

	return 0;
}