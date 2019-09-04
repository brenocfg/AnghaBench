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

__attribute__((used)) static unsigned char
analogix_dp_get_adjust_request_voltage(u8 adjust_request[2], int lane)
{
	int shift = (lane & 1) * 4;
	u8 link_value = adjust_request[lane >> 1];

	return (link_value >> shift) & 0x3;
}