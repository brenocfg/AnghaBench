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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  TWL6032_GPADC_GPCH0_LSB ; 

__attribute__((used)) static u8 twl6032_channel_to_reg(int channel)
{
	/*
	 * for any prior chosen channel, when the conversion is ready
	 * the result is avalable in GPCH0_LSB, GPCH0_MSB.
	 */

	return TWL6032_GPADC_GPCH0_LSB;
}