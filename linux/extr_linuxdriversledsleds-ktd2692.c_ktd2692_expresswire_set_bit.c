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
struct ktd2692_context {int /*<<< orphan*/  ctrl_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTD2692_HIGH ; 
 int /*<<< orphan*/  KTD2692_LOW ; 
 int /*<<< orphan*/  KTD2692_TIME_LONG_BITSET_US ; 
 int /*<<< orphan*/  KTD2692_TIME_SHORT_BITSET_US ; 
 int /*<<< orphan*/  gpiod_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ktd2692_expresswire_set_bit(struct ktd2692_context *led, bool bit)
{
	/*
	 * The Low Bit(0) and High Bit(1) is based on a time detection
	 * algorithm between time low and time high
	 * Time_(L_LB) : Low time of the Low Bit(0)
	 * Time_(H_LB) : High time of the LOW Bit(0)
	 * Time_(L_HB) : Low time of the High Bit(1)
	 * Time_(H_HB) : High time of the High Bit(1)
	 *
	 * It can be simplified to:
	 * Low Bit(0) : 2 * Time_(H_LB) < Time_(L_LB)
	 * High Bit(1) : 2 * Time_(L_HB) < Time_(H_HB)
	 * HIGH  ___           ____    _..     _________    ___
	 *          |_________|    |_..  |____|         |__|
	 * LOW        <L_LB>  <H_LB>     <L_HB>  <H_HB>
	 *          [  Low Bit (0) ]     [  High Bit(1) ]
	 */
	if (bit) {
		gpiod_direction_output(led->ctrl_gpio, KTD2692_LOW);
		udelay(KTD2692_TIME_SHORT_BITSET_US);
		gpiod_direction_output(led->ctrl_gpio, KTD2692_HIGH);
		udelay(KTD2692_TIME_LONG_BITSET_US);
	} else {
		gpiod_direction_output(led->ctrl_gpio, KTD2692_LOW);
		udelay(KTD2692_TIME_LONG_BITSET_US);
		gpiod_direction_output(led->ctrl_gpio, KTD2692_HIGH);
		udelay(KTD2692_TIME_SHORT_BITSET_US);
	}
}