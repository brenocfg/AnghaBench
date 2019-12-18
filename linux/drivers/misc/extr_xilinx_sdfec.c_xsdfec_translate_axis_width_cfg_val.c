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
typedef  enum xsdfec_axis_width { ____Placeholder_xsdfec_axis_width } xsdfec_axis_width ;

/* Variables and functions */
#define  XSDFEC_1x128b 130 
#define  XSDFEC_2x128b 129 
#define  XSDFEC_4x128b 128 

__attribute__((used)) static u32
xsdfec_translate_axis_width_cfg_val(enum xsdfec_axis_width axis_width_cfg)
{
	u32 axis_width_field = 0;

	switch (axis_width_cfg) {
	case XSDFEC_1x128b:
		axis_width_field = 0;
		break;
	case XSDFEC_2x128b:
		axis_width_field = 1;
		break;
	case XSDFEC_4x128b:
		axis_width_field = 2;
		break;
	}

	return axis_width_field;
}