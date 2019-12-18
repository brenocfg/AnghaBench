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

__attribute__((used)) static u8 *to_sas_gpio_gp_bit(unsigned int od, u8 *data, u8 index, u8 count, u8 *bit)
{
	unsigned int reg;
	u8 byte;

	/* gp registers start at index 1 */
	if (index == 0)
		return NULL;

	index--; /* make index 0-based */
	if (od < index * 32)
		return NULL;

	od -= index * 32;
	reg = od >> 5;

	if (reg >= count)
		return NULL;

	od &= (1 << 5) - 1;
	byte = 3 - (od >> 3);
	*bit = od & ((1 << 3) - 1);

	return &data[reg * 4 + byte];
}