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
struct mmci_host {scalar_t__ base; } ;
struct mmc_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ MMCI_STM32_IDMACTRLR ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sdmmc_idma_finalize(struct mmci_host *host, struct mmc_data *data)
{
	writel_relaxed(0, host->base + MMCI_STM32_IDMACTRLR);
}