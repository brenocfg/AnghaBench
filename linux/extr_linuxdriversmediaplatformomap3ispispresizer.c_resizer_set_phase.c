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
struct isp_res_device {int dummy; } ;
struct isp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPRSZ_CNT ; 
 int ISPRSZ_CNT_HSTPH_MASK ; 
 int ISPRSZ_CNT_HSTPH_SHIFT ; 
 int ISPRSZ_CNT_VSTPH_MASK ; 
 int ISPRSZ_CNT_VSTPH_SHIFT ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_RESZ ; 
 int isp_reg_readl (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct isp_device* to_isp_device (struct isp_res_device*) ; 

__attribute__((used)) static void resizer_set_phase(struct isp_res_device *res, u32 h_phase,
			      u32 v_phase)
{
	struct isp_device *isp = to_isp_device(res);
	u32 rgval;

	rgval = isp_reg_readl(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_CNT) &
	      ~(ISPRSZ_CNT_HSTPH_MASK | ISPRSZ_CNT_VSTPH_MASK);
	rgval |= (h_phase << ISPRSZ_CNT_HSTPH_SHIFT) & ISPRSZ_CNT_HSTPH_MASK;
	rgval |= (v_phase << ISPRSZ_CNT_VSTPH_SHIFT) & ISPRSZ_CNT_VSTPH_MASK;

	isp_reg_writel(isp, rgval, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_CNT);
}