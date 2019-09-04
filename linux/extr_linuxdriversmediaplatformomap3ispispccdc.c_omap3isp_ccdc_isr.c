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
struct isp_ccdc_device {scalar_t__ state; } ;

/* Variables and functions */
 int IRQ0STATUS_CCDC_VD0_IRQ ; 
 int IRQ0STATUS_CCDC_VD1_IRQ ; 
 int IRQ0STATUS_HS_VS_IRQ ; 
 scalar_t__ ISP_PIPELINE_STREAM_STOPPED ; 
 int /*<<< orphan*/  ccdc_hs_vs_isr (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  ccdc_lsc_isr (struct isp_ccdc_device*,int) ; 
 int /*<<< orphan*/  ccdc_vd0_isr (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  ccdc_vd1_isr (struct isp_ccdc_device*) ; 

int omap3isp_ccdc_isr(struct isp_ccdc_device *ccdc, u32 events)
{
	if (ccdc->state == ISP_PIPELINE_STREAM_STOPPED)
		return 0;

	if (events & IRQ0STATUS_CCDC_VD1_IRQ)
		ccdc_vd1_isr(ccdc);

	ccdc_lsc_isr(ccdc, events);

	if (events & IRQ0STATUS_CCDC_VD0_IRQ)
		ccdc_vd0_isr(ccdc);

	if (events & IRQ0STATUS_HS_VS_IRQ)
		ccdc_hs_vs_isr(ccdc);

	return 0;
}