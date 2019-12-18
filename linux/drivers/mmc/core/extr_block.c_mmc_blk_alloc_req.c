#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int rel_param; scalar_t__ rel_sectors; } ;
struct TYPE_13__ {int cmds; } ;
struct TYPE_12__ {scalar_t__ mmca_vsn; } ;
struct mmc_card {TYPE_3__ ext_csd; TYPE_2__ scr; TYPE_1__ csd; TYPE_8__* host; } ;
struct TYPE_16__ {int /*<<< orphan*/  queue; struct mmc_blk_data* blkdata; } ;
struct mmc_blk_data {int area_type; int usage; int flags; TYPE_4__* disk; TYPE_7__ queue; scalar_t__ read_only; struct device* parent; int /*<<< orphan*/  rpmbs; int /*<<< orphan*/  part; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_17__ {int index; } ;
struct TYPE_15__ {int first_minor; int flags; int /*<<< orphan*/  disk_name; int /*<<< orphan*/  queue; struct mmc_blk_data* private_data; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; } ;

/* Variables and functions */
 scalar_t__ CSD_SPEC_VER_3 ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENOSPC ; 
 struct mmc_blk_data* ERR_PTR (int) ; 
 int EXT_CSD_WR_REL_PARAM_EN ; 
 int GENHD_FL_EXT_DEVT ; 
 int GENHD_FL_NO_PART_SCAN ; 
 int GENHD_FL_SUPPRESS_PARTITION_INFO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MMC_BLK_CMD23 ; 
 int MMC_BLK_DATA_AREA_BOOT ; 
 int MMC_BLK_DATA_AREA_RPMB ; 
 int MMC_BLK_REL_WR ; 
 int /*<<< orphan*/  MMC_BLOCK_MAJOR ; 
 int SD_SCR_CMD23_SUPPORT ; 
 TYPE_4__* alloc_disk (int) ; 
 int /*<<< orphan*/  blk_get_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_write_cache (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct mmc_blk_data*) ; 
 struct mmc_blk_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_devices ; 
 int /*<<< orphan*/  mmc_bdops ; 
 int /*<<< orphan*/  mmc_blk_ida ; 
 scalar_t__ mmc_blk_readonly (struct mmc_card*) ; 
 scalar_t__ mmc_card_mmc (struct mmc_card*) ; 
 scalar_t__ mmc_card_sd (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_cleanup_queue (TYPE_7__*) ; 
 int /*<<< orphan*/  mmc_dev (TYPE_8__*) ; 
 scalar_t__ mmc_host_cmd23 (TYPE_8__*) ; 
 int mmc_init_queue (TYPE_7__*,struct mmc_card*) ; 
 int perdev_minors ; 
 int /*<<< orphan*/  put_disk (TYPE_4__*) ; 
 int /*<<< orphan*/  set_capacity (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_disk_ro (TYPE_4__*,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,char const*) ; 

__attribute__((used)) static struct mmc_blk_data *mmc_blk_alloc_req(struct mmc_card *card,
					      struct device *parent,
					      sector_t size,
					      bool default_ro,
					      const char *subname,
					      int area_type)
{
	struct mmc_blk_data *md;
	int devidx, ret;

	devidx = ida_simple_get(&mmc_blk_ida, 0, max_devices, GFP_KERNEL);
	if (devidx < 0) {
		/*
		 * We get -ENOSPC because there are no more any available
		 * devidx. The reason may be that, either userspace haven't yet
		 * unmounted the partitions, which postpones mmc_blk_release()
		 * from being called, or the device has more partitions than
		 * what we support.
		 */
		if (devidx == -ENOSPC)
			dev_err(mmc_dev(card->host),
				"no more device IDs available\n");

		return ERR_PTR(devidx);
	}

	md = kzalloc(sizeof(struct mmc_blk_data), GFP_KERNEL);
	if (!md) {
		ret = -ENOMEM;
		goto out;
	}

	md->area_type = area_type;

	/*
	 * Set the read-only status based on the supported commands
	 * and the write protect switch.
	 */
	md->read_only = mmc_blk_readonly(card);

	md->disk = alloc_disk(perdev_minors);
	if (md->disk == NULL) {
		ret = -ENOMEM;
		goto err_kfree;
	}

	INIT_LIST_HEAD(&md->part);
	INIT_LIST_HEAD(&md->rpmbs);
	md->usage = 1;

	ret = mmc_init_queue(&md->queue, card);
	if (ret)
		goto err_putdisk;

	md->queue.blkdata = md;

	/*
	 * Keep an extra reference to the queue so that we can shutdown the
	 * queue (i.e. call blk_cleanup_queue()) while there are still
	 * references to the 'md'. The corresponding blk_put_queue() is in
	 * mmc_blk_put().
	 */
	if (!blk_get_queue(md->queue.queue)) {
		mmc_cleanup_queue(&md->queue);
		ret = -ENODEV;
		goto err_putdisk;
	}

	md->disk->major	= MMC_BLOCK_MAJOR;
	md->disk->first_minor = devidx * perdev_minors;
	md->disk->fops = &mmc_bdops;
	md->disk->private_data = md;
	md->disk->queue = md->queue.queue;
	md->parent = parent;
	set_disk_ro(md->disk, md->read_only || default_ro);
	md->disk->flags = GENHD_FL_EXT_DEVT;
	if (area_type & (MMC_BLK_DATA_AREA_RPMB | MMC_BLK_DATA_AREA_BOOT))
		md->disk->flags |= GENHD_FL_NO_PART_SCAN
				   | GENHD_FL_SUPPRESS_PARTITION_INFO;

	/*
	 * As discussed on lkml, GENHD_FL_REMOVABLE should:
	 *
	 * - be set for removable media with permanent block devices
	 * - be unset for removable block devices with permanent media
	 *
	 * Since MMC block devices clearly fall under the second
	 * case, we do not set GENHD_FL_REMOVABLE.  Userspace
	 * should use the block device creation/destruction hotplug
	 * messages to tell when the card is present.
	 */

	snprintf(md->disk->disk_name, sizeof(md->disk->disk_name),
		 "mmcblk%u%s", card->host->index, subname ? subname : "");

	set_capacity(md->disk, size);

	if (mmc_host_cmd23(card->host)) {
		if ((mmc_card_mmc(card) &&
		     card->csd.mmca_vsn >= CSD_SPEC_VER_3) ||
		    (mmc_card_sd(card) &&
		     card->scr.cmds & SD_SCR_CMD23_SUPPORT))
			md->flags |= MMC_BLK_CMD23;
	}

	if (mmc_card_mmc(card) &&
	    md->flags & MMC_BLK_CMD23 &&
	    ((card->ext_csd.rel_param & EXT_CSD_WR_REL_PARAM_EN) ||
	     card->ext_csd.rel_sectors)) {
		md->flags |= MMC_BLK_REL_WR;
		blk_queue_write_cache(md->queue.queue, true, true);
	}

	return md;

 err_putdisk:
	put_disk(md->disk);
 err_kfree:
	kfree(md);
 out:
	ida_simple_remove(&mmc_blk_ida, devidx);
	return ERR_PTR(ret);
}