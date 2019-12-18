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
struct device {int dummy; } ;
struct armada38x_rtc {int dummy; } ;

/* Variables and functions */
 long DIV_ROUND_CLOSEST (long,int) ; 
 int /*<<< orphan*/  RTC_CCR ; 
 unsigned long RTC_CCR_MODE ; 
 long armada38x_ppb_convert (long) ; 
 long clamp (long,long,long) ; 
 struct armada38x_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_delayed_write (unsigned long,struct armada38x_rtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armada38x_rtc_set_offset(struct device *dev, long offset)
{
	struct armada38x_rtc *rtc = dev_get_drvdata(dev);
	unsigned long ccr = 0;
	long ppb_cor, off;

	/*
	 * The maximum ppb_cor is -128 * 3815 .. 127 * 3815, but we
	 * need to clamp the input.  This equates to -484270 .. 488558.
	 * Not only is this to stop out of range "off" but also to
	 * avoid the division by zero in armada38x_ppb_convert().
	 */
	offset = clamp(offset, -484270L, 488558L);

	ppb_cor = armada38x_ppb_convert(offset);

	/*
	 * Use low update mode where possible, which gives a better
	 * resolution of correction.
	 */
	off = DIV_ROUND_CLOSEST(ppb_cor, 954);
	if (off > 127 || off < -128) {
		ccr = RTC_CCR_MODE;
		off = DIV_ROUND_CLOSEST(ppb_cor, 3815);
	}

	/*
	 * Armada 388 requires a bit pattern in bits 14..8 depending on
	 * the sign bit: { 0, ~S, S, S, S, S, S }
	 */
	ccr |= (off & 0x3fff) ^ 0x2000;
	rtc_delayed_write(ccr, rtc, RTC_CCR);

	return 0;
}