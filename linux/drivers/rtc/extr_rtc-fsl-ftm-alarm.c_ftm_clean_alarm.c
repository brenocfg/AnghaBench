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
 int /*<<< orphan*/  FTM_CNTIN ; 
 int /*<<< orphan*/  FTM_MOD ; 
 int /*<<< orphan*/  ftm_counter_disable (struct ftm_rtc*) ; 
 int /*<<< orphan*/  ftm_reset_counter (struct ftm_rtc*) ; 
 int /*<<< orphan*/  rtc_writel (struct ftm_rtc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void ftm_clean_alarm(struct ftm_rtc *rtc)
{
	ftm_counter_disable(rtc);

	rtc_writel(rtc, FTM_CNTIN, 0x00);
	rtc_writel(rtc, FTM_MOD, ~0U);

	ftm_reset_counter(rtc);
}