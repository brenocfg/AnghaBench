#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ubiblock_pdu {int dummy; } ;
struct TYPE_10__ {int queue_depth; int cmd_size; int nr_hw_queues; struct ubiblock* driver_data; int /*<<< orphan*/  flags; int /*<<< orphan*/  numa_node; int /*<<< orphan*/ * ops; } ;
struct ubiblock {int ubi_num; int vol_id; struct gendisk* gd; TYPE_3__ tag_set; TYPE_1__* rq; int /*<<< orphan*/  list; int /*<<< orphan*/  wq; int /*<<< orphan*/  leb_size; int /*<<< orphan*/  dev_mutex; } ;
struct ubi_volume_info {int ubi_num; int vol_id; int /*<<< orphan*/  name; int /*<<< orphan*/  usable_leb_size; } ;
struct gendisk {scalar_t__ first_minor; int /*<<< orphan*/  disk_name; TYPE_1__* queue; struct ubiblock* private_data; int /*<<< orphan*/  major; int /*<<< orphan*/ * fops; } ;
struct TYPE_9__ {struct ubiblock* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_F_SHOULD_MERGE ; 
 int EEXIST ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  UBI_MAX_SG_COUNT ; 
 int /*<<< orphan*/  add_disk (struct gendisk*) ; 
 struct gendisk* alloc_disk (int) ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (TYPE_1__*) ; 
 int blk_mq_alloc_tag_set (TYPE_3__*) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (TYPE_3__*) ; 
 TYPE_1__* blk_mq_init_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  blk_queue_max_segments (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int calc_disk_capacity (struct ubi_volume_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devices_mutex ; 
 int /*<<< orphan*/  disk_to_dev (struct gendisk*) ; 
 scalar_t__ find_dev_nolock (int,int) ; 
 scalar_t__ idr_alloc (int /*<<< orphan*/ *,struct ubiblock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ubiblock*) ; 
 struct ubiblock* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ubiblock_devices ; 
 int /*<<< orphan*/  ubiblock_major ; 
 int /*<<< orphan*/  ubiblock_minor_idr ; 
 int /*<<< orphan*/  ubiblock_mq_ops ; 
 int /*<<< orphan*/  ubiblock_ops ; 

int ubiblock_create(struct ubi_volume_info *vi)
{
	struct ubiblock *dev;
	struct gendisk *gd;
	u64 disk_capacity;
	int ret;

	ret = calc_disk_capacity(vi, &disk_capacity);
	if (ret) {
		return ret;
	}

	/* Check that the volume isn't already handled */
	mutex_lock(&devices_mutex);
	if (find_dev_nolock(vi->ubi_num, vi->vol_id)) {
		ret = -EEXIST;
		goto out_unlock;
	}

	dev = kzalloc(sizeof(struct ubiblock), GFP_KERNEL);
	if (!dev) {
		ret = -ENOMEM;
		goto out_unlock;
	}

	mutex_init(&dev->dev_mutex);

	dev->ubi_num = vi->ubi_num;
	dev->vol_id = vi->vol_id;
	dev->leb_size = vi->usable_leb_size;

	/* Initialize the gendisk of this ubiblock device */
	gd = alloc_disk(1);
	if (!gd) {
		pr_err("UBI: block: alloc_disk failed\n");
		ret = -ENODEV;
		goto out_free_dev;
	}

	gd->fops = &ubiblock_ops;
	gd->major = ubiblock_major;
	gd->first_minor = idr_alloc(&ubiblock_minor_idr, dev, 0, 0, GFP_KERNEL);
	if (gd->first_minor < 0) {
		dev_err(disk_to_dev(gd),
			"block: dynamic minor allocation failed");
		ret = -ENODEV;
		goto out_put_disk;
	}
	gd->private_data = dev;
	sprintf(gd->disk_name, "ubiblock%d_%d", dev->ubi_num, dev->vol_id);
	set_capacity(gd, disk_capacity);
	dev->gd = gd;

	dev->tag_set.ops = &ubiblock_mq_ops;
	dev->tag_set.queue_depth = 64;
	dev->tag_set.numa_node = NUMA_NO_NODE;
	dev->tag_set.flags = BLK_MQ_F_SHOULD_MERGE;
	dev->tag_set.cmd_size = sizeof(struct ubiblock_pdu);
	dev->tag_set.driver_data = dev;
	dev->tag_set.nr_hw_queues = 1;

	ret = blk_mq_alloc_tag_set(&dev->tag_set);
	if (ret) {
		dev_err(disk_to_dev(dev->gd), "blk_mq_alloc_tag_set failed");
		goto out_remove_minor;
	}

	dev->rq = blk_mq_init_queue(&dev->tag_set);
	if (IS_ERR(dev->rq)) {
		dev_err(disk_to_dev(gd), "blk_mq_init_queue failed");
		ret = PTR_ERR(dev->rq);
		goto out_free_tags;
	}
	blk_queue_max_segments(dev->rq, UBI_MAX_SG_COUNT);

	dev->rq->queuedata = dev;
	dev->gd->queue = dev->rq;

	/*
	 * Create one workqueue per volume (per registered block device).
	 * Rembember workqueues are cheap, they're not threads.
	 */
	dev->wq = alloc_workqueue("%s", 0, 0, gd->disk_name);
	if (!dev->wq) {
		ret = -ENOMEM;
		goto out_free_queue;
	}

	list_add_tail(&dev->list, &ubiblock_devices);

	/* Must be the last step: anyone can call file ops from now on */
	add_disk(dev->gd);
	dev_info(disk_to_dev(dev->gd), "created from ubi%d:%d(%s)",
		 dev->ubi_num, dev->vol_id, vi->name);
	mutex_unlock(&devices_mutex);
	return 0;

out_free_queue:
	blk_cleanup_queue(dev->rq);
out_free_tags:
	blk_mq_free_tag_set(&dev->tag_set);
out_remove_minor:
	idr_remove(&ubiblock_minor_idr, gd->first_minor);
out_put_disk:
	put_disk(dev->gd);
out_free_dev:
	kfree(dev);
out_unlock:
	mutex_unlock(&devices_mutex);

	return ret;
}