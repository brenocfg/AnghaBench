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
typedef  unsigned int u32 ;
struct au1xmmc_host {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_CONFIG (struct au1xmmc_host*) ; 
 unsigned int SD_CONFIG_DE ; 
 unsigned int SD_CONFIG_DIV ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void au1xmmc_set_clock(struct au1xmmc_host *host, int rate)
{
	unsigned int pbus = clk_get_rate(host->clk);
	unsigned int divisor = ((pbus / rate) / 2) - 1;
	u32 config;

	config = __raw_readl(HOST_CONFIG(host));

	config &= ~(SD_CONFIG_DIV);
	config |= (divisor & SD_CONFIG_DIV) | SD_CONFIG_DE;

	__raw_writel(config, HOST_CONFIG(host));
	wmb(); /* drain writebuffer */
}