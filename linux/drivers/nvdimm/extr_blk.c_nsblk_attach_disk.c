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
typedef  int u64 ;
struct request_queue {int /*<<< orphan*/  disk_name; int /*<<< orphan*/  flags; struct request_queue* queue; int /*<<< orphan*/ * fops; scalar_t__ first_minor; struct nd_namespace_blk* queuedata; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct nd_namespace_blk {TYPE_1__ common; int /*<<< orphan*/  size; } ;
struct gendisk {int /*<<< orphan*/  disk_name; int /*<<< orphan*/  flags; struct gendisk* queue; int /*<<< orphan*/ * fops; scalar_t__ first_minor; struct nd_namespace_blk* queuedata; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GENHD_FL_EXT_DEVT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  UINT_MAX ; 
 struct request_queue* alloc_disk (int /*<<< orphan*/ ) ; 
 struct request_queue* blk_alloc_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_queue_make_request (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_disk (struct device*,struct request_queue*,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct request_queue*) ; 
 int div_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_blk_fops ; 
 int /*<<< orphan*/  nd_blk_make_request ; 
 int /*<<< orphan*/  nd_blk_release_disk ; 
 int /*<<< orphan*/  nd_blk_release_queue ; 
 int nd_integrity_init (struct request_queue*,scalar_t__) ; 
 int /*<<< orphan*/  nsblk_internal_lbasize (struct nd_namespace_blk*) ; 
 scalar_t__ nsblk_meta_size (struct nd_namespace_blk*) ; 
 int nsblk_sector_size (struct nd_namespace_blk*) ; 
 int /*<<< orphan*/  nvdimm_namespace_disk_name (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revalidate_disk (struct request_queue*) ; 
 int /*<<< orphan*/  set_capacity (struct request_queue*,int) ; 

__attribute__((used)) static int nsblk_attach_disk(struct nd_namespace_blk *nsblk)
{
	struct device *dev = &nsblk->common.dev;
	resource_size_t available_disk_size;
	struct request_queue *q;
	struct gendisk *disk;
	u64 internal_nlba;

	internal_nlba = div_u64(nsblk->size, nsblk_internal_lbasize(nsblk));
	available_disk_size = internal_nlba * nsblk_sector_size(nsblk);

	q = blk_alloc_queue(GFP_KERNEL);
	if (!q)
		return -ENOMEM;
	if (devm_add_action_or_reset(dev, nd_blk_release_queue, q))
		return -ENOMEM;

	blk_queue_make_request(q, nd_blk_make_request);
	blk_queue_max_hw_sectors(q, UINT_MAX);
	blk_queue_logical_block_size(q, nsblk_sector_size(nsblk));
	blk_queue_flag_set(QUEUE_FLAG_NONROT, q);
	q->queuedata = nsblk;

	disk = alloc_disk(0);
	if (!disk)
		return -ENOMEM;

	disk->first_minor	= 0;
	disk->fops		= &nd_blk_fops;
	disk->queue		= q;
	disk->flags		= GENHD_FL_EXT_DEVT;
	nvdimm_namespace_disk_name(&nsblk->common, disk->disk_name);

	if (devm_add_action_or_reset(dev, nd_blk_release_disk, disk))
		return -ENOMEM;

	if (nsblk_meta_size(nsblk)) {
		int rc = nd_integrity_init(disk, nsblk_meta_size(nsblk));

		if (rc)
			return rc;
	}

	set_capacity(disk, available_disk_size >> SECTOR_SHIFT);
	device_add_disk(dev, disk, NULL);
	revalidate_disk(disk);
	return 0;
}