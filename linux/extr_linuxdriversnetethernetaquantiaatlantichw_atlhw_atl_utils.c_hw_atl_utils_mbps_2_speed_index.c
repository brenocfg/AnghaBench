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

unsigned int hw_atl_utils_mbps_2_speed_index(unsigned int mbps)
{
	unsigned int ret = 0U;

	switch (mbps) {
	case 100U:
		ret = 5U;
		break;

	case 1000U:
		ret = 4U;
		break;

	case 2500U:
		ret = 3U;
		break;

	case 5000U:
		ret = 1U;
		break;

	case 10000U:
		ret = 0U;
		break;

	default:
		break;
	}
	return ret;
}