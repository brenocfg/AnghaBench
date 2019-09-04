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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static bool check_gamma5_errata(u32 gamma5)
{
	int i;

	for (i = 0; i < 3; i++) {
		if (((gamma5 >> i*8) & 0xff) == 0x80)
			return false;
	}

	return true;
}