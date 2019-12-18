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
typedef  int uint32_t ;
struct jz4740_mmc_host {scalar_t__ base; } ;

/* Variables and functions */
 int JZ_MMC_STATUS_CLK_EN ; 
 int /*<<< orphan*/  JZ_MMC_STRPCL_CLOCK_STOP ; 
 scalar_t__ JZ_REG_MMC_STATUS ; 
 scalar_t__ JZ_REG_MMC_STRPCL ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void jz4740_mmc_clock_disable(struct jz4740_mmc_host *host)
{
	uint32_t status;
	unsigned int timeout = 1000;

	writew(JZ_MMC_STRPCL_CLOCK_STOP, host->base + JZ_REG_MMC_STRPCL);
	do {
		status = readl(host->base + JZ_REG_MMC_STATUS);
	} while (status & JZ_MMC_STATUS_CLK_EN && --timeout);
}