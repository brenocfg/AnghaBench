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
#define  ETM_ARCH_V3_3 131 
#define  ETM_ARCH_V3_5 130 
#define  PFT_ARCH_V1_0 129 
#define  PFT_ARCH_V1_1 128 

__attribute__((used)) static bool etm_arch_supported(u8 arch)
{
	switch (arch) {
	case ETM_ARCH_V3_3:
		break;
	case ETM_ARCH_V3_5:
		break;
	case PFT_ARCH_V1_0:
		break;
	case PFT_ARCH_V1_1:
		break;
	default:
		return false;
	}
	return true;
}