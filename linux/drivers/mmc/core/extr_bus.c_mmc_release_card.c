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
struct mmc_card {struct mmc_card* info; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mmc_card*) ; 
 struct mmc_card* mmc_dev_to_card (struct device*) ; 
 int /*<<< orphan*/  sdio_free_common_cis (struct mmc_card*) ; 

__attribute__((used)) static void mmc_release_card(struct device *dev)
{
	struct mmc_card *card = mmc_dev_to_card(dev);

	sdio_free_common_cis(card);

	kfree(card->info);

	kfree(card);
}