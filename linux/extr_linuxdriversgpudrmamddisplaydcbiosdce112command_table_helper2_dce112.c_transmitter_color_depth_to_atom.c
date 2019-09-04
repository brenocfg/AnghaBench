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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum transmitter_color_depth { ____Placeholder_transmitter_color_depth } transmitter_color_depth ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_2_1 ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_3_2 ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_5_4 ; 
 int /*<<< orphan*/  PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_DIS ; 
#define  TRANSMITTER_COLOR_DEPTH_24 131 
#define  TRANSMITTER_COLOR_DEPTH_30 130 
#define  TRANSMITTER_COLOR_DEPTH_36 129 
#define  TRANSMITTER_COLOR_DEPTH_48 128 

__attribute__((used)) static uint8_t transmitter_color_depth_to_atom(enum transmitter_color_depth id)
{
	uint8_t atomColorDepth = 0;

	switch (id) {
	case TRANSMITTER_COLOR_DEPTH_24:
		atomColorDepth = PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_DIS;
		break;
	case TRANSMITTER_COLOR_DEPTH_30:
		atomColorDepth = PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_5_4;
		break;
	case TRANSMITTER_COLOR_DEPTH_36:
		atomColorDepth = PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_3_2;
		break;
	case TRANSMITTER_COLOR_DEPTH_48:
		atomColorDepth = PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_2_1;
		break;
	default:
		ASSERT_CRITICAL(false); /* Unhandle action in driver! */
		break;
	}

	return atomColorDepth;
}