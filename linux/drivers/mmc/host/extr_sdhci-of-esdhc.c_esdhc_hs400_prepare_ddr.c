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
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  esdhc_tuning_block_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static int esdhc_hs400_prepare_ddr(struct mmc_host *mmc)
{
	esdhc_tuning_block_enable(mmc_priv(mmc), false);
	return 0;
}