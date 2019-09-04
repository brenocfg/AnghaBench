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
typedef  enum ipu_color_space { ____Placeholder_ipu_color_space } ipu_color_space ;

/* Variables and functions */
 int IPUV3_COLORSPACE_RGB ; 
 int IPUV3_COLORSPACE_UNKNOWN ; 
 int IPUV3_COLORSPACE_YUV ; 

enum ipu_color_space ipu_mbus_code_to_colorspace(u32 mbus_code)
{
	switch (mbus_code & 0xf000) {
	case 0x1000:
		return IPUV3_COLORSPACE_RGB;
	case 0x2000:
		return IPUV3_COLORSPACE_YUV;
	default:
		return IPUV3_COLORSPACE_UNKNOWN;
	}
}