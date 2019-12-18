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
struct meson_rtc {int /*<<< orphan*/  peripheral; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_ADDR1 ; 
 int RTC_ADDR1_SDO ; 
 int RTC_DATA_BITS ; 
 int /*<<< orphan*/  meson_rtc_sclk_pulse (struct meson_rtc*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static u32 meson_rtc_get_data(struct meson_rtc *rtc)
{
	u32 tmp, val = 0;
	int bit;

	for (bit = 0; bit < RTC_DATA_BITS; bit++) {
		meson_rtc_sclk_pulse(rtc);
		val <<= 1;

		regmap_read(rtc->peripheral, RTC_ADDR1, &tmp);
		val |= tmp & RTC_ADDR1_SDO;
	}

	return val;
}