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

__attribute__((used)) static inline unsigned long em28xx_hash_mem(char *buf, int length, int bits)
{
	unsigned long hash = 0;
	unsigned long l = 0;
	int len = 0;
	unsigned char c;

	do {
		if (len == length) {
			c = (char)len;
			len = -1;
		} else {
			c = *buf++;
		}
		l = (l << 8) | c;
		len++;
		if ((len & (32 / 8 - 1)) == 0)
			hash = ((hash ^ l) * 0x9e370001UL);
	} while (len);

	return (hash >> (32 - bits)) & 0xffffffffUL;
}