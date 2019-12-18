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
struct etm_drvdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETMCR ; 
 int /*<<< orphan*/  ETMCR_PWD_DWN ; 
 int /*<<< orphan*/  etm_readl (struct etm_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etm_writel (struct etm_drvdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void etm_clr_pwrdwn(struct etm_drvdata *drvdata)
{
	u32 etmcr;

	etmcr = etm_readl(drvdata, ETMCR);
	etmcr &= ~ETMCR_PWD_DWN;
	etm_writel(drvdata, etmcr, ETMCR);
	/* Ensure pwrup completes before subsequent cp14 accesses */
	mb();
	isb();
}