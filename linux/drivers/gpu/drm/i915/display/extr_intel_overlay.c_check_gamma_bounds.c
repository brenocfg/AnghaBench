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

__attribute__((used)) static bool check_gamma_bounds(u32 gamma1, u32 gamma2)
{
	int i;

	if (gamma1 & 0xff000000 || gamma2 & 0xff000000)
		return false;

	for (i = 0; i < 3; i++) {
		if (((gamma1 >> i*8) & 0xff) >= ((gamma2 >> i*8) & 0xff))
			return false;
	}

	return true;
}