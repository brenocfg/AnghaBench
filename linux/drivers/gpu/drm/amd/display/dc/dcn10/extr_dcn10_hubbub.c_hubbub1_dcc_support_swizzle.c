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
typedef  enum swizzle_mode_values { ____Placeholder_swizzle_mode_values } swizzle_mode_values ;
typedef  enum segment_order { ____Placeholder_segment_order } segment_order ;

/* Variables and functions */
#define  DC_SW_4KB_D 139 
#define  DC_SW_4KB_D_X 138 
#define  DC_SW_4KB_S 137 
#define  DC_SW_4KB_S_X 136 
#define  DC_SW_64KB_D 135 
#define  DC_SW_64KB_D_X 134 
#define  DC_SW_64KB_S 133 
#define  DC_SW_64KB_S_X 132 
#define  DC_SW_VAR_D 131 
#define  DC_SW_VAR_D_X 130 
#define  DC_SW_VAR_S 129 
#define  DC_SW_VAR_S_X 128 
 int segment_order__contiguous ; 
 int segment_order__na ; 
 int segment_order__non_contiguous ; 

__attribute__((used)) static bool hubbub1_dcc_support_swizzle(
		enum swizzle_mode_values swizzle,
		unsigned int bytes_per_element,
		enum segment_order *segment_order_horz,
		enum segment_order *segment_order_vert)
{
	bool standard_swizzle = false;
	bool display_swizzle = false;

	switch (swizzle) {
	case DC_SW_4KB_S:
	case DC_SW_64KB_S:
	case DC_SW_VAR_S:
	case DC_SW_4KB_S_X:
	case DC_SW_64KB_S_X:
	case DC_SW_VAR_S_X:
		standard_swizzle = true;
		break;
	case DC_SW_4KB_D:
	case DC_SW_64KB_D:
	case DC_SW_VAR_D:
	case DC_SW_4KB_D_X:
	case DC_SW_64KB_D_X:
	case DC_SW_VAR_D_X:
		display_swizzle = true;
		break;
	default:
		break;
	}

	if (bytes_per_element == 1 && standard_swizzle) {
		*segment_order_horz = segment_order__contiguous;
		*segment_order_vert = segment_order__na;
		return true;
	}
	if (bytes_per_element == 2 && standard_swizzle) {
		*segment_order_horz = segment_order__non_contiguous;
		*segment_order_vert = segment_order__contiguous;
		return true;
	}
	if (bytes_per_element == 4 && standard_swizzle) {
		*segment_order_horz = segment_order__non_contiguous;
		*segment_order_vert = segment_order__contiguous;
		return true;
	}
	if (bytes_per_element == 8 && standard_swizzle) {
		*segment_order_horz = segment_order__na;
		*segment_order_vert = segment_order__contiguous;
		return true;
	}
	if (bytes_per_element == 8 && display_swizzle) {
		*segment_order_horz = segment_order__contiguous;
		*segment_order_vert = segment_order__non_contiguous;
		return true;
	}

	return false;
}