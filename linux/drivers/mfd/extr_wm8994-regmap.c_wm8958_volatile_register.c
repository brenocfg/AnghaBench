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
struct device {int dummy; } ;

/* Variables and functions */
#define  WM8958_DSP2_CONFIGXMEM 148 
#define  WM8958_DSP2_CONFIGYMEM 147 
#define  WM8958_DSP2_CONFIGZMEM 146 
#define  WM8958_DSP2_EXECCONTROL 145 
#define  WM8958_DSP2_MAGICNUM 144 
#define  WM8958_DSP2_RELEASEMONTHDAY 143 
#define  WM8958_DSP2_RELEASETIME 142 
#define  WM8958_DSP2_RELEASEYEAR 141 
#define  WM8958_DSP2_SWVERSIONREG 140 
#define  WM8958_DSP2_VERBUILD 139 
#define  WM8958_DSP2_VERMAJMIN 138 
#define  WM8958_FW_BUILD_0 137 
#define  WM8958_FW_BUILD_1 136 
#define  WM8958_FW_ID_0 135 
#define  WM8958_FW_ID_1 134 
#define  WM8958_FW_MAJOR_0 133 
#define  WM8958_FW_MAJOR_1 132 
#define  WM8958_FW_MINOR_0 131 
#define  WM8958_FW_MINOR_1 130 
#define  WM8958_FW_PATCH_0 129 
#define  WM8958_FW_PATCH_1 128 
 int wm8994_volatile_register (struct device*,unsigned int) ; 

__attribute__((used)) static bool wm8958_volatile_register(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case WM8958_DSP2_MAGICNUM:
	case WM8958_DSP2_RELEASEYEAR:
	case WM8958_DSP2_RELEASEMONTHDAY:
	case WM8958_DSP2_RELEASETIME:
	case WM8958_DSP2_VERMAJMIN:
	case WM8958_DSP2_VERBUILD:
	case WM8958_DSP2_EXECCONTROL:
	case WM8958_DSP2_SWVERSIONREG:
	case WM8958_DSP2_CONFIGXMEM:
	case WM8958_DSP2_CONFIGYMEM:
	case WM8958_DSP2_CONFIGZMEM:
	case WM8958_FW_BUILD_1:
	case WM8958_FW_BUILD_0:
	case WM8958_FW_ID_1:
	case WM8958_FW_ID_0:
	case WM8958_FW_MAJOR_1:
	case WM8958_FW_MAJOR_0:
	case WM8958_FW_MINOR_1:
	case WM8958_FW_MINOR_0:
	case WM8958_FW_PATCH_1:
	case WM8958_FW_PATCH_0:
		return true;
	default:
		return wm8994_volatile_register(dev, reg);
	}
}