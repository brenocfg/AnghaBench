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
typedef  int u32 ;

/* Variables and functions */
 void** table_com ; 

int
l1oip_law_to_4bit(u8 *data, int len, u8 *result, u32 *state)
{
	int ii, i = 0, o = 0;

	if (!len)
		return 0;

	/* send saved byte and first input byte */
	if (*state) {
		*result++ = table_com[(((*state) << 8) & 0xff00) | (*data++)];
		len--;
		o++;
	}

	ii = len >> 1;

	while (i < ii) {
		*result++ = table_com[(data[0]<<8) | (data[1])];
		data += 2;
		i++;
		o++;
	}

	/* if len has an odd number, we save byte for next call */
	if (len & 1)
		*state = 0x100 + *data;
	else
		*state = 0;

	return o;
}