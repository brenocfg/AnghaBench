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
struct isp_res_device {int dummy; } ;
struct isp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPRSZ_PCR ; 
 int ISPRSZ_PCR_ENABLE ; 
 int ISPRSZ_PCR_ONESHOT ; 
 int /*<<< orphan*/  OMAP3_ISP_IOMEM_RESZ ; 
 int /*<<< orphan*/  isp_reg_set (struct isp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct isp_device* to_isp_device (struct isp_res_device*) ; 

__attribute__((used)) static void resizer_enable_oneshot(struct isp_res_device *res)
{
	struct isp_device *isp = to_isp_device(res);

	isp_reg_set(isp, OMAP3_ISP_IOMEM_RESZ, ISPRSZ_PCR,
		    ISPRSZ_PCR_ENABLE | ISPRSZ_PCR_ONESHOT);
}