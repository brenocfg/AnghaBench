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
 int FIELD_PREP (int,int) ; 
 int /*<<< orphan*/  RTC_ADDR0 ; 
 int RTC_ADDR0_DATA ; 
 int RTC_ADDR0_START_SER ; 
 int RTC_ADDR0_WAIT_SER ; 
 int /*<<< orphan*/  RTC_REG4 ; 
 int RTC_REG4_STATIC_VALUE ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int meson_rtc_write_static(struct meson_rtc *rtc, u32 data)
{
	u32 tmp;

	regmap_write(rtc->peripheral, RTC_REG4,
		     FIELD_PREP(RTC_REG4_STATIC_VALUE, (data >> 8)));

	/* write the static value and start the auto serializer */
	tmp = FIELD_PREP(RTC_ADDR0_DATA, (data & 0xff)) | RTC_ADDR0_START_SER;
	regmap_update_bits(rtc->peripheral, RTC_ADDR0,
			   RTC_ADDR0_DATA | RTC_ADDR0_START_SER, tmp);

	/* wait for the auto serializer to complete */
	return regmap_read_poll_timeout(rtc->peripheral, RTC_REG4, tmp,
					!(tmp & RTC_ADDR0_WAIT_SER), 10,
					10000);
}