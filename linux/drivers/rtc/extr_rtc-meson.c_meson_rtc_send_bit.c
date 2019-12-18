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
struct meson_rtc {int /*<<< orphan*/  peripheral; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_ADDR0 ; 
 int /*<<< orphan*/  RTC_ADDR0_LINE_SDI ; 
 int /*<<< orphan*/  meson_rtc_sclk_pulse (struct meson_rtc*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson_rtc_send_bit(struct meson_rtc *rtc, unsigned int bit)
{
	regmap_update_bits(rtc->peripheral, RTC_ADDR0, RTC_ADDR0_LINE_SDI,
			   bit ? RTC_ADDR0_LINE_SDI : 0);
	meson_rtc_sclk_pulse(rtc);
}