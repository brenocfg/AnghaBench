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
typedef  long u8 ;
struct it87_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ has_newer_autopwm (struct it87_data const*) ; 

__attribute__((used)) static u8 pwm_to_reg(const struct it87_data *data, long val)
{
	if (has_newer_autopwm(data))
		return val;
	else
		return val >> 1;
}