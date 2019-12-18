#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct cache_sb {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  bi_inline_vecs; } ;
struct cache {int /*<<< orphan*/  cache_dev_name; int /*<<< orphan*/  kobj; int /*<<< orphan*/  sb; int /*<<< orphan*/  discard; TYPE_2__ sb_bio; struct block_device* bdev; } ;
struct block_device {int /*<<< orphan*/  bd_part; struct cache* bd_holder; } ;
struct TYPE_7__ {struct page* bv_page; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_DISCARD (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPERM ; 
 int FMODE_EXCL ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  bch_register_lock ; 
 int /*<<< orphan*/  bdev_get_queue (struct block_device*) ; 
 int /*<<< orphan*/  bdevname (struct block_device*,int /*<<< orphan*/ ) ; 
 TYPE_3__* bio_first_bvec_all (TYPE_2__*) ; 
 int /*<<< orphan*/  bio_init (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ blk_queue_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blkdev_put (struct block_device*,int) ; 
 int cache_alloc (struct cache*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 scalar_t__ kobject_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct cache_sb*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* part_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ,char const*) ; 
 char* register_cache_set (struct cache*) ; 

__attribute__((used)) static int register_cache(struct cache_sb *sb, struct page *sb_page,
				struct block_device *bdev, struct cache *ca)
{
	const char *err = NULL; /* must be set for any error case */
	int ret = 0;

	bdevname(bdev, ca->cache_dev_name);
	memcpy(&ca->sb, sb, sizeof(struct cache_sb));
	ca->bdev = bdev;
	ca->bdev->bd_holder = ca;

	bio_init(&ca->sb_bio, ca->sb_bio.bi_inline_vecs, 1);
	bio_first_bvec_all(&ca->sb_bio)->bv_page = sb_page;
	get_page(sb_page);

	if (blk_queue_discard(bdev_get_queue(bdev)))
		ca->discard = CACHE_DISCARD(&ca->sb);

	ret = cache_alloc(ca);
	if (ret != 0) {
		/*
		 * If we failed here, it means ca->kobj is not initialized yet,
		 * kobject_put() won't be called and there is no chance to
		 * call blkdev_put() to bdev in bch_cache_release(). So we
		 * explicitly call blkdev_put() here.
		 */
		blkdev_put(bdev, FMODE_READ|FMODE_WRITE|FMODE_EXCL);
		if (ret == -ENOMEM)
			err = "cache_alloc(): -ENOMEM";
		else if (ret == -EPERM)
			err = "cache_alloc(): cache device is too small";
		else
			err = "cache_alloc(): unknown error";
		goto err;
	}

	if (kobject_add(&ca->kobj,
			&part_to_dev(bdev->bd_part)->kobj,
			"bcache")) {
		err = "error calling kobject_add";
		ret = -ENOMEM;
		goto out;
	}

	mutex_lock(&bch_register_lock);
	err = register_cache_set(ca);
	mutex_unlock(&bch_register_lock);

	if (err) {
		ret = -ENODEV;
		goto out;
	}

	pr_info("registered cache device %s", ca->cache_dev_name);

out:
	kobject_put(&ca->kobj);

err:
	if (err)
		pr_notice("error %s: %s", ca->cache_dev_name, err);

	return ret;
}