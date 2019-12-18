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
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 133 
#define  COLOR_DEPTH_121212 132 
#define  COLOR_DEPTH_141414 131 
#define  COLOR_DEPTH_161616 130 
#define  COLOR_DEPTH_666 129 
#define  COLOR_DEPTH_888 128 

__attribute__((used)) static int get_color_depth(enum dc_color_depth color_depth)
{
	switch (color_depth) {
	case COLOR_DEPTH_666: return 6;
	case COLOR_DEPTH_888: return 8;
	case COLOR_DEPTH_101010: return 10;
	case COLOR_DEPTH_121212: return 12;
	case COLOR_DEPTH_141414: return 14;
	case COLOR_DEPTH_161616: return 16;
	default: return 0;
	}
}