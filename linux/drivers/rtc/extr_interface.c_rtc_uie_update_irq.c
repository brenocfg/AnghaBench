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
struct rtc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_UF ; 
 int /*<<< orphan*/  rtc_handle_legacy_irq (struct rtc_device*,int,int /*<<< orphan*/ ) ; 

void rtc_uie_update_irq(struct rtc_device *rtc)
{
	rtc_handle_legacy_irq(rtc, 1,  RTC_UF);
}