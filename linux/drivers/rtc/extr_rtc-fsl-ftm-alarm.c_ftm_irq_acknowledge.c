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
struct ftm_rtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTM_SC ; 
 int FTM_SC_TOF ; 
 int rtc_readl (struct ftm_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_writel (struct ftm_rtc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ftm_irq_acknowledge(struct ftm_rtc *rtc)
{
	unsigned int timeout = 100;

	/*
	 *Fix errata A-007728 for flextimer
	 *	If the FTM counter reaches the FTM_MOD value between
	 *	the reading of the TOF bit and the writing of 0 to
	 *	the TOF bit, the process of clearing the TOF bit
	 *	does not work as expected when FTMx_CONF[NUMTOF] != 0
	 *	and the current TOF count is less than FTMx_CONF[NUMTOF].
	 *	If the above condition is met, the TOF bit remains set.
	 *	If the TOF interrupt is enabled (FTMx_SC[TOIE] = 1),the
	 *	TOF interrupt also remains asserted.
	 *
	 *	Above is the errata discription
	 *
	 *	In one word: software clearing TOF bit not works when
	 *	FTMx_CONF[NUMTOF] was seted as nonzero and FTM counter
	 *	reaches the FTM_MOD value.
	 *
	 *	The workaround is clearing TOF bit until it works
	 *	(FTM counter doesn't always reache the FTM_MOD anyway),
	 *	which may cost some cycles.
	 */
	while ((FTM_SC_TOF & rtc_readl(rtc, FTM_SC)) && timeout--)
		rtc_writel(rtc, FTM_SC, rtc_readl(rtc, FTM_SC) & (~FTM_SC_TOF));
}