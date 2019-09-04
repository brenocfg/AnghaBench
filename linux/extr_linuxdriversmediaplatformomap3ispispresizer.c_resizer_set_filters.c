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
typedef  int u16 ;
struct isp_res_device {int dummy; } ;
struct isp_device {int dummy; } ;

/* Variables and functions */
 int COEFF_CNT ; 
 int ISPRSZ_HFILT10 ; 
 int const ISPRSZ_HFILT_COEF1_SHIFT ; 
 int ISPRSZ_VFILT10 ; 
 int const ISPRSZ_VFILT_COEF1_SHIFT ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_RESZ ; 
 int /*<<< orphan*/  isp_reg_writel (struct isp_device*,int,int /*<<< orphan*/ ,int) ; 
 struct isp_device* to_isp_device (struct isp_res_device*) ; 

__attribute__((used)) static void resizer_set_filters(struct isp_res_device *res, const u16 *h_coeff,
				const u16 *v_coeff)
{
	struct isp_device *isp = to_isp_device(res);
	u32 startaddr_h, startaddr_v, tmp_h, tmp_v;
	int i;

	startaddr_h = ISPRSZ_HFILT10;
	startaddr_v = ISPRSZ_VFILT10;

	for (i = 0; i < COEFF_CNT; i += 2) {
		tmp_h = h_coeff[i] |
			(h_coeff[i + 1] << ISPRSZ_HFILT_COEF1_SHIFT);
		tmp_v = v_coeff[i] |
			(v_coeff[i + 1] << ISPRSZ_VFILT_COEF1_SHIFT);
		isp_reg_writel(isp, tmp_h, OMAP3_ISP_IOMEM_RESZ, startaddr_h);
		isp_reg_writel(isp, tmp_v, OMAP3_ISP_IOMEM_RESZ, startaddr_v);
		startaddr_h += 4;
		startaddr_v += 4;
	}
}