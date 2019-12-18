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
 int /*<<< orphan*/  RTC_ADDR0_LINE_SEN ; 
 int /*<<< orphan*/  RTC_ADDR_BITS ; 
 int meson_rtc_get_bus (struct meson_rtc*) ; 
 unsigned int meson_rtc_get_data (struct meson_rtc*) ; 
 int /*<<< orphan*/  meson_rtc_send_bits (struct meson_rtc*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_rtc_set_dir (struct meson_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_rtc_serial_bus_reg_read(void *context, unsigned int reg,
					 unsigned int *data)
{
	struct meson_rtc *rtc = context;
	int ret;

	ret = meson_rtc_get_bus(rtc);
	if (ret)
		return ret;

	regmap_update_bits(rtc->peripheral, RTC_ADDR0, RTC_ADDR0_LINE_SEN,
			   RTC_ADDR0_LINE_SEN);
	meson_rtc_send_bits(rtc, reg, RTC_ADDR_BITS);
	meson_rtc_set_dir(rtc, 0);
	*data = meson_rtc_get_data(rtc);

	return 0;
}