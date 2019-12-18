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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static u16 cpcap_led_val(u8 current_limit, u8 duty_cycle)
{
	current_limit &= 0x1f; /* 5 bit */
	duty_cycle &= 0x0f; /* 4 bit */

	return current_limit << 4 | duty_cycle;
}