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

/* Variables and functions */
 int /*<<< orphan*/  MCF_GPT_GMS0 ; 
 unsigned int MCF_GPT_GMS_OCPW (int) ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wdt_keepalive(void)
{
	unsigned int gms0;

	gms0 = __raw_readl(MCF_GPT_GMS0);
	gms0 |= MCF_GPT_GMS_OCPW(0xA5);
	__raw_writel(gms0, MCF_GPT_GMS0);
}