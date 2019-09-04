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

__attribute__((used)) static inline unsigned char
FlipBits(unsigned char c, int keylen)
{
	unsigned char b = c;
	unsigned char bit = 128;
	int i;
	int j;
	int hunks = (8 / keylen);

	c = 0;
	for (i = 0; i < hunks; i++) {
		for (j = 0; j < keylen; j++) {
			if (b & (bit >> j))
				c |= bit >> (keylen - j - 1);
		}
		bit >>= keylen;
	}
	return c;
}