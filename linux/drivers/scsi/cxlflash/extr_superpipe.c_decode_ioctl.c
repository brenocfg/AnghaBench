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
#define  DK_CXLFLASH_ATTACH 137 
#define  DK_CXLFLASH_DETACH 136 
#define  DK_CXLFLASH_MANAGE_LUN 135 
#define  DK_CXLFLASH_RECOVER_AFU 134 
#define  DK_CXLFLASH_RELEASE 133 
#define  DK_CXLFLASH_USER_DIRECT 132 
#define  DK_CXLFLASH_USER_VIRTUAL 131 
#define  DK_CXLFLASH_VERIFY 130 
#define  DK_CXLFLASH_VLUN_CLONE 129 
#define  DK_CXLFLASH_VLUN_RESIZE 128 
 char* __stringify_1 (int const) ; 

__attribute__((used)) static char *decode_ioctl(unsigned int cmd)
{
	switch (cmd) {
	case DK_CXLFLASH_ATTACH:
		return __stringify_1(DK_CXLFLASH_ATTACH);
	case DK_CXLFLASH_USER_DIRECT:
		return __stringify_1(DK_CXLFLASH_USER_DIRECT);
	case DK_CXLFLASH_USER_VIRTUAL:
		return __stringify_1(DK_CXLFLASH_USER_VIRTUAL);
	case DK_CXLFLASH_VLUN_RESIZE:
		return __stringify_1(DK_CXLFLASH_VLUN_RESIZE);
	case DK_CXLFLASH_RELEASE:
		return __stringify_1(DK_CXLFLASH_RELEASE);
	case DK_CXLFLASH_DETACH:
		return __stringify_1(DK_CXLFLASH_DETACH);
	case DK_CXLFLASH_VERIFY:
		return __stringify_1(DK_CXLFLASH_VERIFY);
	case DK_CXLFLASH_VLUN_CLONE:
		return __stringify_1(DK_CXLFLASH_VLUN_CLONE);
	case DK_CXLFLASH_RECOVER_AFU:
		return __stringify_1(DK_CXLFLASH_RECOVER_AFU);
	case DK_CXLFLASH_MANAGE_LUN:
		return __stringify_1(DK_CXLFLASH_MANAGE_LUN);
	}

	return "UNKNOWN";
}