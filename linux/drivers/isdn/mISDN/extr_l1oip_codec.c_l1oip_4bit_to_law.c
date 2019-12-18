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
typedef  int u16 ;

/* Variables and functions */
 int* table_dec ; 

int
l1oip_4bit_to_law(u8 *data, int len, u8 *result)
{
	int i = 0;
	u16 r;

	while (i < len) {
		r = table_dec[*data++];
		*result++ = r >> 8;
		*result++ = r;
		i++;
	}

	return len << 1;
}