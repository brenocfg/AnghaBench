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
 int /*<<< orphan*/  ISPH3A_PCR ; 
 int ISPH3A_PCR_BUSYAEAWB ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_H3A ; 
 int isp_reg_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int h3a_aewb_busy(struct ispstat *aewb)
{
	return isp_reg_readl(aewb->isp, OMAP3_ISP_IOMEM_H3A, ISPH3A_PCR)
						& ISPH3A_PCR_BUSYAEAWB;
}