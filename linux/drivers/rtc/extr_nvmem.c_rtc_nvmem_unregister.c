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
struct rtc_device {scalar_t__ nvram; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtc_nvram_unregister (struct rtc_device*) ; 

void rtc_nvmem_unregister(struct rtc_device *rtc)
{
	/* unregister the old ABI */
	if (rtc->nvram)
		rtc_nvram_unregister(rtc);
}