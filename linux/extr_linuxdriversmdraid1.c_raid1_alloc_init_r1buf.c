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
struct resync_pages {int dummy; } ;
struct r1conf {TYPE_1__* poolinfo; int /*<<< orphan*/  r1buf_pool; } ;
struct r1bio {int /*<<< orphan*/ * master_bio; struct bio** bios; } ;
struct bio {struct resync_pages* bi_private; } ;
struct TYPE_2__ {int raid_disks; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  bio_reset (struct bio*) ; 
 struct r1bio* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct r1bio *raid1_alloc_init_r1buf(struct r1conf *conf)
{
	struct r1bio *r1bio = mempool_alloc(&conf->r1buf_pool, GFP_NOIO);
	struct resync_pages *rps;
	struct bio *bio;
	int i;

	for (i = conf->poolinfo->raid_disks; i--; ) {
		bio = r1bio->bios[i];
		rps = bio->bi_private;
		bio_reset(bio);
		bio->bi_private = rps;
	}
	r1bio->master_bio = NULL;
	return r1bio;
}