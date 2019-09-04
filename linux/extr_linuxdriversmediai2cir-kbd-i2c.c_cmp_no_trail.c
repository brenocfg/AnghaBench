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

__attribute__((used)) static int cmp_no_trail(u8 *a, u8 *b, unsigned int count)
{
	while (--count) {
		if (*a++ != *b++)
			return 1;
	}

	return (*a & 0xf0) - (*b & 0xf0);
}