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
 int EINVAL ; 

__attribute__((used)) static int omap2_onenand_get_freq(int ver)
{
	switch ((ver >> 4) & 0xf) {
	case 0:
		return 40;
	case 1:
		return 54;
	case 2:
		return 66;
	case 3:
		return 83;
	case 4:
		return 104;
	}

	return -EINVAL;
}