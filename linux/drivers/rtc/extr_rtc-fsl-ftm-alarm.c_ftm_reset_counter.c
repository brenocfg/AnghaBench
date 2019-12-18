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
 int /*<<< orphan*/  FTM_CNT ; 
 int /*<<< orphan*/  rtc_writel (struct ftm_rtc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ftm_reset_counter(struct ftm_rtc *rtc)
{
	/*
	 * The CNT register contains the FTM counter value.
	 * Reset clears the CNT register. Writing any value to COUNT
	 * updates the counter with its initial value, CNTIN.
	 */
	rtc_writel(rtc, FTM_CNT, 0x00);
}