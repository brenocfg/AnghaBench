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

__attribute__((used)) static unsigned command_2_index(u8 c, u8 sc)
{
	if (c & 0x80)
		c = 0x9 + (c & 0x0f);
	else if (c == 0x41)
		c = 0x9 + 0x1;
	if (c > 0x18)
		c = 0x00;
	return (sc & 3) * (0x9 + 0x9) + c;
}