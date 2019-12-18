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
struct sprd_rtc {scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRD_RTC_ALM_INT_MASK ; 
 scalar_t__ SPRD_RTC_INT_CLR ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sprd_rtc_clear_alarm_ints(struct sprd_rtc *rtc)
{
	return regmap_write(rtc->regmap, rtc->base + SPRD_RTC_INT_CLR,
			    SPRD_RTC_ALM_INT_MASK);
}