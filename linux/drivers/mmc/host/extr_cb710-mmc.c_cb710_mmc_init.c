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
typedef  int u32 ;
struct platform_device {int dummy; } ;
struct mmc_host {int f_max; int f_min; int ocr_avail; int /*<<< orphan*/  caps; int /*<<< orphan*/ * ops; } ;
struct cb710_slot {int dummy; } ;
struct cb710_mmc_reader {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  finish_req_tasklet; } ;
struct cb710_chip {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB710_DUMP_REGS_MMC ; 
 size_t CB710_MAX_DIVIDER_IDX ; 
 int /*<<< orphan*/  CB710_MMC_IE_CARD_INSERTION_STATUS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MMC_CAP_4_BIT_DATA ; 
 int MMC_VDD_32_33 ; 
 int MMC_VDD_33_34 ; 
 int* cb710_clock_divider_log2 ; 
 int /*<<< orphan*/  cb710_dump_regs (struct cb710_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_mmc_enable_irq (struct cb710_slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_mmc_finish_request_tasklet ; 
 int /*<<< orphan*/  cb710_mmc_host ; 
 int /*<<< orphan*/ * cb710_mmc_irq_handler ; 
 struct cb710_slot* cb710_pdev_to_slot (struct platform_device*) ; 
 int /*<<< orphan*/  cb710_set_irq_handler (struct cb710_slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cb710_slot_dev (struct cb710_slot*) ; 
 struct cb710_chip* cb710_slot_to_chip (struct cb710_slot*) ; 
 int* cb710_src_freq_mhz ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int mmc_add_host (struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 int mmc_hostname (struct mmc_host*) ; 
 struct cb710_mmc_reader* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mmc_host*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cb710_mmc_init(struct platform_device *pdev)
{
	struct cb710_slot *slot = cb710_pdev_to_slot(pdev);
	struct cb710_chip *chip = cb710_slot_to_chip(slot);
	struct mmc_host *mmc;
	struct cb710_mmc_reader *reader;
	int err;
	u32 val;

	mmc = mmc_alloc_host(sizeof(*reader), cb710_slot_dev(slot));
	if (!mmc)
		return -ENOMEM;

	platform_set_drvdata(pdev, mmc);

	/* harmless (maybe) magic */
	pci_read_config_dword(chip->pdev, 0x48, &val);
	val = cb710_src_freq_mhz[(val >> 16) & 0xF];
	dev_dbg(cb710_slot_dev(slot), "source frequency: %dMHz\n", val);
	val *= 1000000;

	mmc->ops = &cb710_mmc_host;
	mmc->f_max = val;
	mmc->f_min = val >> cb710_clock_divider_log2[CB710_MAX_DIVIDER_IDX];
	mmc->ocr_avail = MMC_VDD_32_33|MMC_VDD_33_34;
	mmc->caps = MMC_CAP_4_BIT_DATA;

	reader = mmc_priv(mmc);

	tasklet_init(&reader->finish_req_tasklet,
		cb710_mmc_finish_request_tasklet, (unsigned long)mmc);
	spin_lock_init(&reader->irq_lock);
	cb710_dump_regs(chip, CB710_DUMP_REGS_MMC);

	cb710_mmc_enable_irq(slot, 0, ~0);
	cb710_set_irq_handler(slot, cb710_mmc_irq_handler);

	err = mmc_add_host(mmc);
	if (unlikely(err))
		goto err_free_mmc;

	dev_dbg(cb710_slot_dev(slot), "mmc_hostname is %s\n",
		mmc_hostname(mmc));

	cb710_mmc_enable_irq(slot, CB710_MMC_IE_CARD_INSERTION_STATUS, 0);

	return 0;

err_free_mmc:
	dev_dbg(cb710_slot_dev(slot), "mmc_add_host() failed: %d\n", err);

	cb710_set_irq_handler(slot, NULL);
	mmc_free_host(mmc);
	return err;
}