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
struct au1xmmc_host {int dummy; } ;

/* Variables and functions */
 int AU1XMMC_INTERRUPTS ; 
 int /*<<< orphan*/  HOST_BLKSIZE (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  HOST_CONFIG (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  HOST_CONFIG2 (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  HOST_ENABLE (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  HOST_STATUS (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  HOST_TIMEOUT (struct au1xmmc_host*) ; 
 int SD_CONFIG2_EN ; 
 int SD_CONFIG2_FF ; 
 int SD_ENABLE_CE ; 
 int SD_ENABLE_R ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void au1xmmc_reset_controller(struct au1xmmc_host *host)
{
	/* Apply the clock */
	__raw_writel(SD_ENABLE_CE, HOST_ENABLE(host));
	wmb(); /* drain writebuffer */
	mdelay(1);

	__raw_writel(SD_ENABLE_R | SD_ENABLE_CE, HOST_ENABLE(host));
	wmb(); /* drain writebuffer */
	mdelay(5);

	__raw_writel(~0, HOST_STATUS(host));
	wmb(); /* drain writebuffer */

	__raw_writel(0, HOST_BLKSIZE(host));
	__raw_writel(0x001fffff, HOST_TIMEOUT(host));
	wmb(); /* drain writebuffer */

	__raw_writel(SD_CONFIG2_EN, HOST_CONFIG2(host));
	wmb(); /* drain writebuffer */

	__raw_writel(SD_CONFIG2_EN | SD_CONFIG2_FF, HOST_CONFIG2(host));
	wmb(); /* drain writebuffer */
	mdelay(1);

	__raw_writel(SD_CONFIG2_EN, HOST_CONFIG2(host));
	wmb(); /* drain writebuffer */

	/* Configure interrupts */
	__raw_writel(AU1XMMC_INTERRUPTS, HOST_CONFIG(host));
	wmb(); /* drain writebuffer */
}