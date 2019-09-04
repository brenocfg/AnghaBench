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
struct isp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IRQ0ENABLE ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_MAIN ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isp_disable_interrupts(struct isp_device *isp)
{
	isp_reg_writel(isp, 0, OMAP3_ISP_IOMEM_MAIN, ISP_IRQ0ENABLE);
}