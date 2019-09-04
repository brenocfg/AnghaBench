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
struct ispstat {int /*<<< orphan*/  isp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPHIST_PCR ; 
 int ISPHIST_PCR_BUSY ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_HIST ; 
 int isp_reg_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hist_busy(struct ispstat *hist)
{
	return isp_reg_readl(hist->isp, OMAP3_ISP_IOMEM_HIST, ISPHIST_PCR)
						& ISPHIST_PCR_BUSY;
}