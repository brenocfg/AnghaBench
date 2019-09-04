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
struct isp_prev_device {int dummy; } ;
struct isp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPPRV_AVE ; 
 int ISPPRV_AVE_EVENDIST_2 ; 
 int ISPPRV_AVE_EVENDIST_SHIFT ; 
 int ISPPRV_AVE_ODDDIST_2 ; 
 int ISPPRV_AVE_ODDDIST_SHIFT ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_PREV ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_prev_device*) ; 

__attribute__((used)) static void preview_config_averager(struct isp_prev_device *prev, u8 average)
{
	struct isp_device *isp = to_isp_device(prev);

	isp_reg_writel(isp, ISPPRV_AVE_EVENDIST_2 << ISPPRV_AVE_EVENDIST_SHIFT |
		       ISPPRV_AVE_ODDDIST_2 << ISPPRV_AVE_ODDDIST_SHIFT |
		       average, OMAP3_ISP_IOMEM_PREV, ISPPRV_AVE);
}