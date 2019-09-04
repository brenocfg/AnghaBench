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
typedef  int /*<<< orphan*/  u32 ;
struct au1xmmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_CONFIG (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void IRQ_OFF(struct au1xmmc_host *host, u32 mask)
{
	u32 val = __raw_readl(HOST_CONFIG(host));
	val &= ~mask;
	__raw_writel(val, HOST_CONFIG(host));
	wmb(); /* drain writebuffer */
}