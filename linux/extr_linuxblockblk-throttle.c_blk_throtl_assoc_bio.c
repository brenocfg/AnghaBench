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
struct throtl_grp {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void blk_throtl_assoc_bio(struct throtl_grp *tg, struct bio *bio)
{
#ifdef CONFIG_BLK_DEV_THROTTLING_LOW
	/* fallback to root_blkg if we fail to get a blkg ref */
	if (bio->bi_css && (bio_associate_blkg(bio, tg_to_blkg(tg)) == -ENODEV))
		bio_associate_blkg(bio, bio->bi_disk->queue->root_blkg);
	bio_issue_init(&bio->bi_issue, bio_sectors(bio));
#endif
}