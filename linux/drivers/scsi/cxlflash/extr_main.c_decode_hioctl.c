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
#define  HT_CXLFLASH_LUN_PROVISION 128 
 char* __stringify_1 (int const) ; 

__attribute__((used)) static char *decode_hioctl(unsigned int cmd)
{
	switch (cmd) {
	case HT_CXLFLASH_LUN_PROVISION:
		return __stringify_1(HT_CXLFLASH_LUN_PROVISION);
	}

	return "UNKNOWN";
}