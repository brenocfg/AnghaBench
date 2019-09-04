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
struct au1xmmc_host {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_CMD (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  HOST_CONFIG2 (struct au1xmmc_host*) ; 
 scalar_t__ HOST_S_DATA ; 
 scalar_t__ HOST_S_STOP ; 
 int SD_CONFIG2_DF ; 
 int STOP_CMD ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void SEND_STOP(struct au1xmmc_host *host)
{
	u32 config2;

	WARN_ON(host->status != HOST_S_DATA);
	host->status = HOST_S_STOP;

	config2 = __raw_readl(HOST_CONFIG2(host));
	__raw_writel(config2 | SD_CONFIG2_DF, HOST_CONFIG2(host));
	wmb(); /* drain writebuffer */

	/* Send the stop command */
	__raw_writel(STOP_CMD, HOST_CMD(host));
	wmb(); /* drain writebuffer */
}