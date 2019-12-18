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
 int ENOTSUPP ; 

__attribute__((used)) static int bm1880_pinconf_drv_get(u32 width, u32 drv)
{
	int ret = -ENOTSUPP;

	/*
	 * There are two sets of drive strength bit width exposed by the
	 * SoC at 4mA step, hence we need to handle them separately.
	 */
	if (width == 0x03) {
		switch (drv) {
		case 0:
			ret  = 4;
			break;
		case 1:
			ret  = 8;
			break;
		case 2:
			ret  = 12;
			break;
		case 3:
			ret  = 16;
			break;
		case 4:
			ret  = 20;
			break;
		case 5:
			ret  = 24;
			break;
		case 6:
			ret  = 28;
			break;
		case 7:
			ret  = 32;
			break;
		default:
			break;
		}
	} else {
		switch (drv) {
		case 0:
			ret  = 4;
			break;
		case 1:
			ret  = 8;
			break;
		case 2:
			ret  = 12;
			break;
		case 3:
			ret  = 16;
			break;
		default:
			break;
		}
	}

	return ret;
}