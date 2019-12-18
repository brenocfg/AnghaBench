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
struct mxc_rtc_data {scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ SRTC_LPCR ; 
 int SRTC_LPCR_ALP ; 
 int SRTC_LPCR_WAE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mxc_rtc_alarm_irq_enable_locked(struct mxc_rtc_data *pdata,
					    unsigned int enable)
{
	u32 lp_cr = readl(pdata->ioaddr + SRTC_LPCR);

	if (enable)
		lp_cr |= (SRTC_LPCR_ALP | SRTC_LPCR_WAE);
	else
		lp_cr &= ~(SRTC_LPCR_ALP | SRTC_LPCR_WAE);

	writel(lp_cr, pdata->ioaddr + SRTC_LPCR);
}