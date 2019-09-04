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
struct etm_drvdata {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ETMPDCR ; 
 int /*<<< orphan*/  ETMPDCR_PWD_UP ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void etm_clr_pwrup(struct etm_drvdata *drvdata)
{
	u32 etmpdcr;

	/* Ensure pending cp14 accesses complete before clearing pwrup */
	mb();
	isb();
	etmpdcr = readl_relaxed(drvdata->base + ETMPDCR);
	etmpdcr &= ~ETMPDCR_PWD_UP;
	writel_relaxed(etmpdcr, drvdata->base + ETMPDCR);
}