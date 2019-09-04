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

inline bool is_buswidth_valid(u8 buswidth, bool is_mpc8308)
{
	switch (buswidth) {
	case 16:
		if (is_mpc8308)
			return false;
	case 1:
	case 2:
	case 4:
	case 32:
		break;
	default:
		return false;
	}

	return true;
}