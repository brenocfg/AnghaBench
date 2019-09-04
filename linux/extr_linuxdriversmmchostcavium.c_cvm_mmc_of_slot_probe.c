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
struct mmc_host {int caps; int max_segs; int max_seg_size; int max_req_size; int max_blk_size; int max_blk_count; int /*<<< orphan*/  f_min; int /*<<< orphan*/ * ops; } ;
struct device {int dummy; } ;
struct cvm_mmc_slot {int bus_id; int cached_rca; struct mmc_host* mmc; struct cvm_mmc_host* host; int /*<<< orphan*/  clock; } ;
struct cvm_mmc_host {struct cvm_mmc_slot** slot; int /*<<< orphan*/  (* release_bus ) (struct cvm_mmc_host*) ;int /*<<< orphan*/  (* acquire_bus ) (struct cvm_mmc_host*) ;scalar_t__ use_sg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MMC_CAP_3_3V_DDR ; 
 int MMC_CAP_CMD23 ; 
 int MMC_CAP_ERASE ; 
 int MMC_CAP_MMC_HIGHSPEED ; 
 int MMC_CAP_POWER_OFF_CARD ; 
 int MMC_CAP_SD_HIGHSPEED ; 
 int /*<<< orphan*/  cvm_mmc_init_lowlevel (struct cvm_mmc_slot*) ; 
 int cvm_mmc_of_parse (struct device*,struct cvm_mmc_slot*) ; 
 int /*<<< orphan*/  cvm_mmc_ops ; 
 int /*<<< orphan*/  cvm_mmc_switch_to (struct cvm_mmc_slot*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int mmc_add_host (struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,struct device*) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct cvm_mmc_slot* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  stub1 (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  stub2 (struct cvm_mmc_host*) ; 

int cvm_mmc_of_slot_probe(struct device *dev, struct cvm_mmc_host *host)
{
	struct cvm_mmc_slot *slot;
	struct mmc_host *mmc;
	int ret, id;

	mmc = mmc_alloc_host(sizeof(struct cvm_mmc_slot), dev);
	if (!mmc)
		return -ENOMEM;

	slot = mmc_priv(mmc);
	slot->mmc = mmc;
	slot->host = host;

	ret = cvm_mmc_of_parse(dev, slot);
	if (ret < 0)
		goto error;
	id = ret;

	/* Set up host parameters */
	mmc->ops = &cvm_mmc_ops;

	/*
	 * We only have a 3.3v supply, we cannot support any
	 * of the UHS modes. We do support the high speed DDR
	 * modes up to 52MHz.
	 *
	 * Disable bounce buffers for max_segs = 1
	 */
	mmc->caps |= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED |
		     MMC_CAP_ERASE | MMC_CAP_CMD23 | MMC_CAP_POWER_OFF_CARD |
		     MMC_CAP_3_3V_DDR;

	if (host->use_sg)
		mmc->max_segs = 16;
	else
		mmc->max_segs = 1;

	/* DMA size field can address up to 8 MB */
	mmc->max_seg_size = 8 * 1024 * 1024;
	mmc->max_req_size = mmc->max_seg_size;
	/* External DMA is in 512 byte blocks */
	mmc->max_blk_size = 512;
	/* DMA block count field is 15 bits */
	mmc->max_blk_count = 32767;

	slot->clock = mmc->f_min;
	slot->bus_id = id;
	slot->cached_rca = 1;

	host->acquire_bus(host);
	host->slot[id] = slot;
	cvm_mmc_switch_to(slot);
	cvm_mmc_init_lowlevel(slot);
	host->release_bus(host);

	ret = mmc_add_host(mmc);
	if (ret) {
		dev_err(dev, "mmc_add_host() returned %d\n", ret);
		slot->host->slot[id] = NULL;
		goto error;
	}
	return 0;

error:
	mmc_free_host(slot->mmc);
	return ret;
}