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

__attribute__((used)) static void copy_codes(u8 *dst, u8 *src, unsigned int count)
{
	u8 c, last = 0xff;

	while (count--) {
		c = *src++;
		if ((c & 0xf0) == last) {
			*dst++ = 0x70 | (c & 0xf);
		} else {
			*dst++ = c;
			last = c & 0xf0;
		}
	}
}