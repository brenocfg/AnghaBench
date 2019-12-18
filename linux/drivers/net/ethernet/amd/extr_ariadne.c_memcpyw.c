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
typedef  int u_short ;
typedef  int u_char ;

/* Variables and functions */

__attribute__((used)) static void memcpyw(volatile u_short *dest, u_short *src, int len)
{
	while (len >= 2) {
		*(dest++) = *(src++);
		len -= 2;
	}
	if (len == 1)
		*dest = (*(u_char *)src) << 8;
}