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
struct resizer_luma_yenh {int algo; int gain; int slope; int core; } ;
struct isp_res_device {int dummy; } ;
struct isp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPRSZ_YENH ; 
 int ISPRSZ_YENH_ALGO_MASK ; 
 int ISPRSZ_YENH_ALGO_SHIFT ; 
 int ISPRSZ_YENH_CORE_MASK ; 
 int ISPRSZ_YENH_CORE_SHIFT ; 
 int ISPRSZ_YENH_GAIN_MASK ; 
 int ISPRSZ_YENH_GAIN_SHIFT ; 
 int ISPRSZ_YENH_SLOP_MASK ; 
 int ISPRSZ_YENH_SLOP_SHIFT ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_RESZ ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_res_device*) ; 

__attribute__((used)) static void resizer_set_luma(struct isp_res_device *res,
			     struct resizer_luma_yenh *luma)
{
	struct isp_device *isp = to_isp_device(res);
	u32 rgval;

	rgval  = (luma->algo << ISPRSZ_YENH_ALGO_SHIFT)
		  & ISPRSZ_YENH_ALGO_MASK;
	rgval |= (luma->gain << ISPRSZ_YENH_GAIN_SHIFT)
		  & ISPRSZ_YENH_GAIN_MASK;
	rgval |= (luma->slope << ISPRSZ_YENH_SLOP_SHIFT)
		  & ISPRSZ_YENH_SLOP_MASK;
	rgval |= (luma->core << ISPRSZ_YENH_CORE_SHIFT)
		  & ISPRSZ_YENH_CORE_MASK;

	isp_reg_writel(isp, rgval, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_YENH);
}