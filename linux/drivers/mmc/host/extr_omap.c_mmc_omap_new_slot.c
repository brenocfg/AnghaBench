#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mmc_omap_slot {int id; TYPE_2__* pdata; int /*<<< orphan*/  cover_tasklet; int /*<<< orphan*/  cover_timer; int /*<<< orphan*/  power_mode; struct mmc_host* mmc; struct mmc_omap_host* host; } ;
struct mmc_omap_host {TYPE_1__* pdata; struct mmc_omap_slot** slots; int /*<<< orphan*/  dev; } ;
struct mmc_host {int caps; int f_min; int f_max; int max_segs; int max_blk_size; int max_blk_count; int max_req_size; int max_seg_size; int /*<<< orphan*/  class_dev; int /*<<< orphan*/  ocr_avail; int /*<<< orphan*/ * ops; } ;
struct TYPE_4__ {int wires; int /*<<< orphan*/ * name; int /*<<< orphan*/ * get_cover_state; int /*<<< orphan*/  ocr_mask; } ;
struct TYPE_3__ {scalar_t__ max_freq; TYPE_2__* slots; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MMC_CAP_4_BIT_DATA ; 
 int MMC_CAP_ERASE ; 
 int /*<<< orphan*/  MMC_POWER_UNDEFINED ; 
 int /*<<< orphan*/  dev_attr_cover_switch ; 
 int /*<<< orphan*/  dev_attr_slot_name ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int min (scalar_t__,int) ; 
 int mmc_add_host (struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 scalar_t__ mmc_omap2 () ; 
 int /*<<< orphan*/  mmc_omap_cover_handler ; 
 int /*<<< orphan*/  mmc_omap_cover_timer ; 
 int /*<<< orphan*/  mmc_omap_ops ; 
 struct mmc_omap_slot* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_omap_new_slot(struct mmc_omap_host *host, int id)
{
	struct mmc_omap_slot *slot = NULL;
	struct mmc_host *mmc;
	int r;

	mmc = mmc_alloc_host(sizeof(struct mmc_omap_slot), host->dev);
	if (mmc == NULL)
		return -ENOMEM;

	slot = mmc_priv(mmc);
	slot->host = host;
	slot->mmc = mmc;
	slot->id = id;
	slot->power_mode = MMC_POWER_UNDEFINED;
	slot->pdata = &host->pdata->slots[id];

	host->slots[id] = slot;

	mmc->caps = 0;
	if (host->pdata->slots[id].wires >= 4)
		mmc->caps |= MMC_CAP_4_BIT_DATA | MMC_CAP_ERASE;

	mmc->ops = &mmc_omap_ops;
	mmc->f_min = 400000;

	if (mmc_omap2())
		mmc->f_max = 48000000;
	else
		mmc->f_max = 24000000;
	if (host->pdata->max_freq)
		mmc->f_max = min(host->pdata->max_freq, mmc->f_max);
	mmc->ocr_avail = slot->pdata->ocr_mask;

	/* Use scatterlist DMA to reduce per-transfer costs.
	 * NOTE max_seg_size assumption that small blocks aren't
	 * normally used (except e.g. for reading SD registers).
	 */
	mmc->max_segs = 32;
	mmc->max_blk_size = 2048;	/* BLEN is 11 bits (+1) */
	mmc->max_blk_count = 2048;	/* NBLK is 11 bits (+1) */
	mmc->max_req_size = mmc->max_blk_size * mmc->max_blk_count;
	mmc->max_seg_size = mmc->max_req_size;

	if (slot->pdata->get_cover_state != NULL) {
		timer_setup(&slot->cover_timer, mmc_omap_cover_timer, 0);
		tasklet_init(&slot->cover_tasklet, mmc_omap_cover_handler,
			     (unsigned long)slot);
	}

	r = mmc_add_host(mmc);
	if (r < 0)
		goto err_remove_host;

	if (slot->pdata->name != NULL) {
		r = device_create_file(&mmc->class_dev,
					&dev_attr_slot_name);
		if (r < 0)
			goto err_remove_host;
	}

	if (slot->pdata->get_cover_state != NULL) {
		r = device_create_file(&mmc->class_dev,
					&dev_attr_cover_switch);
		if (r < 0)
			goto err_remove_slot_name;
		tasklet_schedule(&slot->cover_tasklet);
	}

	return 0;

err_remove_slot_name:
	if (slot->pdata->name != NULL)
		device_remove_file(&mmc->class_dev, &dev_attr_slot_name);
err_remove_host:
	mmc_remove_host(mmc);
	mmc_free_host(mmc);
	return r;
}