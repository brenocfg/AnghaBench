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
typedef  int u32 ;
struct davinci_rtc {int /*<<< orphan*/  rtc; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  PRTCIF_INTFLG ; 
 int PRTCIF_INTFLG_RTCSS ; 
 int /*<<< orphan*/  PRTCSS_RTC_CCTRL ; 
 int PRTCSS_RTC_CCTRL_ALMFLG ; 
 int /*<<< orphan*/  PRTCSS_RTC_CTRL ; 
 int PRTCSS_RTC_CTRL_TMRFLG ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 unsigned long RTC_PF ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,unsigned long) ; 
 int rtcif_read (struct davinci_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtcif_write (struct davinci_rtc*,int,int /*<<< orphan*/ ) ; 
 int rtcss_read (struct davinci_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtcss_write (struct davinci_rtc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t davinci_rtc_interrupt(int irq, void *class_dev)
{
	struct davinci_rtc *davinci_rtc = class_dev;
	unsigned long events = 0;
	u32 irq_flg;
	u8 alm_irq, tmr_irq;
	u8 rtc_ctrl, rtc_cctrl;
	int ret = IRQ_NONE;

	irq_flg = rtcif_read(davinci_rtc, PRTCIF_INTFLG) &
		  PRTCIF_INTFLG_RTCSS;

	alm_irq = rtcss_read(davinci_rtc, PRTCSS_RTC_CCTRL) &
		  PRTCSS_RTC_CCTRL_ALMFLG;

	tmr_irq = rtcss_read(davinci_rtc, PRTCSS_RTC_CTRL) &
		  PRTCSS_RTC_CTRL_TMRFLG;

	if (irq_flg) {
		if (alm_irq) {
			events |= RTC_IRQF | RTC_AF;
			rtc_cctrl = rtcss_read(davinci_rtc, PRTCSS_RTC_CCTRL);
			rtc_cctrl |=  PRTCSS_RTC_CCTRL_ALMFLG;
			rtcss_write(davinci_rtc, rtc_cctrl, PRTCSS_RTC_CCTRL);
		} else if (tmr_irq) {
			events |= RTC_IRQF | RTC_PF;
			rtc_ctrl = rtcss_read(davinci_rtc, PRTCSS_RTC_CTRL);
			rtc_ctrl |=  PRTCSS_RTC_CTRL_TMRFLG;
			rtcss_write(davinci_rtc, rtc_ctrl, PRTCSS_RTC_CTRL);
		}

		rtcif_write(davinci_rtc, PRTCIF_INTFLG_RTCSS,
				    PRTCIF_INTFLG);
		rtc_update_irq(davinci_rtc->rtc, 1, events);

		ret = IRQ_HANDLED;
	}

	return ret;
}