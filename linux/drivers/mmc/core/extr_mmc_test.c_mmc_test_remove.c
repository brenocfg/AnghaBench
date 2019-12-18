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
struct mmc_card {int /*<<< orphan*/  host; scalar_t__ reenable_cmdq; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_cmdq_enable (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_release_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_test_free_dbgfs_file (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_test_free_result (struct mmc_card*) ; 

__attribute__((used)) static void mmc_test_remove(struct mmc_card *card)
{
	if (card->reenable_cmdq) {
		mmc_claim_host(card->host);
		mmc_cmdq_enable(card);
		mmc_release_host(card->host);
	}
	mmc_test_free_result(card);
	mmc_test_free_dbgfs_file(card);
}