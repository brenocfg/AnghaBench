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

/* Variables and functions */

__attribute__((used)) static unsigned char dht11_decode_byte(char *bits)
{
	unsigned char ret = 0;
	int i;

	for (i = 0; i < 8; ++i) {
		ret <<= 1;
		if (bits[i])
			++ret;
	}

	return ret;
}