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
struct platform_device {int dummy; } ;
struct mmc_host {int dummy; } ;
struct cb710_slot {int dummy; } ;
struct cb710_mmc_reader {int /*<<< orphan*/  finish_req_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CB710_MMC_CONFIGB_PORT ; 
 int /*<<< orphan*/  CB710_MMC_CONFIG_PORT ; 
 int /*<<< orphan*/  CB710_MMC_IE_CARD_INSERTION_STATUS ; 
 int /*<<< orphan*/  cb710_mmc_enable_irq (struct cb710_slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cb710_slot* cb710_pdev_to_slot (struct platform_device*) ; 
 int /*<<< orphan*/  cb710_set_irq_handler (struct cb710_slot*,int /*<<< orphan*/ *) ; 
 struct mmc_host* cb710_slot_to_mmc (struct cb710_slot*) ; 
 int /*<<< orphan*/  cb710_write_port_16 (struct cb710_slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb710_write_port_32 (struct cb710_slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct cb710_mmc_reader* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cb710_mmc_exit(struct platform_device *pdev)
{
	struct cb710_slot *slot = cb710_pdev_to_slot(pdev);
	struct mmc_host *mmc = cb710_slot_to_mmc(slot);
	struct cb710_mmc_reader *reader = mmc_priv(mmc);

	cb710_mmc_enable_irq(slot, 0, CB710_MMC_IE_CARD_INSERTION_STATUS);

	mmc_remove_host(mmc);

	/* IRQs should be disabled now, but let's stay on the safe side */
	cb710_mmc_enable_irq(slot, 0, ~0);
	cb710_set_irq_handler(slot, NULL);

	/* clear config ports - just in case */
	cb710_write_port_32(slot, CB710_MMC_CONFIG_PORT, 0);
	cb710_write_port_16(slot, CB710_MMC_CONFIGB_PORT, 0);

	tasklet_kill(&reader->finish_req_tasklet);

	mmc_free_host(mmc);
	return 0;
}