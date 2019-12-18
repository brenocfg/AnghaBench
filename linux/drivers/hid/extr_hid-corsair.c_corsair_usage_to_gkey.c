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

__attribute__((used)) static int corsair_usage_to_gkey(unsigned int usage)
{
	/* G1 (0xd0) to G16 (0xdf) */
	if (usage >= 0xd0 && usage <= 0xdf)
		return usage - 0xd0 + 1;
	/* G17 (0xe8) to G18 (0xe9) */
	if (usage >= 0xe8 && usage <= 0xe9)
		return usage - 0xe8 + 17;
	return 0;
}