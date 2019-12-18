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
typedef  int u8 ;

/* Variables and functions */
 int DAC_LIMIT (int) ; 

__attribute__((used)) static u8 pwm_to_dac(unsigned int pwm, bool v12)
{
	int limit = DAC_LIMIT(v12);

	return limit - (limit * pwm) / 255;
}