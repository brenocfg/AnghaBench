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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ptp_dte {scalar_t__ regs; int /*<<< orphan*/  ptp_clk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int DTE_NUM_REGS_TO_RESTORE ; 
 struct ptp_dte* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ptp_dte_remove(struct platform_device *pdev)
{
	struct ptp_dte *ptp_dte = platform_get_drvdata(pdev);
	u8 i;

	ptp_clock_unregister(ptp_dte->ptp_clk);

	for (i = 0; i < DTE_NUM_REGS_TO_RESTORE; i++)
		writel(0, ptp_dte->regs + (i * sizeof(u32)));

	return 0;
}