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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static u16 get_bits_per_mask(u16 byte_mask)
{
	u16 bits = 0;

	while (byte_mask) {
		byte_mask = byte_mask & (byte_mask - 1);
		bits++;
	}

	return bits;
}