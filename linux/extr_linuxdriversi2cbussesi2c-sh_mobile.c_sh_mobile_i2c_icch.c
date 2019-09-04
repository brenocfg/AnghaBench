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
typedef  unsigned long u32 ;

/* Variables and functions */

__attribute__((used)) static u32 sh_mobile_i2c_icch(unsigned long count_khz, u32 tHIGH, u32 tf)
{
	/*
	 * Conditional expression:
	 *   ICCH >= COUNT_CLK * (tHIGH + tf)
	 *
	 * SH-Mobile IIC hardware is aware of SCL transition period 'tr',
	 * and can ignore it.  SH-Mobile IIC controller starts counting
	 * the HIGH period of the SCL signal (tHIGH) after the SCL input
	 * voltage increases at VIH.
	 *
	 * Afterward it turned out calculating ICCH using only tHIGH spec
	 * will result in violation of the tHD;STA timing spec.  We need
	 * to take into account the fall time of SDA signal (tf) at START
	 * condition, in order to meet both tHIGH and tHD;STA specs.
	 */
	return (((count_khz * (tHIGH + tf)) + 5000) / 10000);
}