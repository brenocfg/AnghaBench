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

__attribute__((used)) static u8 ixgbe_ones_comp_byte_add(u8 add1, u8 add2)
{
	u16 sum = add1 + add2;

	sum = (sum & 0xFF) + (sum >> 8);
	return sum & 0xFF;
}