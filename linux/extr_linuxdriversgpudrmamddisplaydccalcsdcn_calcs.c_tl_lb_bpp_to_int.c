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
typedef  enum lb_pixel_depth { ____Placeholder_lb_pixel_depth } lb_pixel_depth ;

/* Variables and functions */
#define  LB_PIXEL_DEPTH_18BPP 131 
#define  LB_PIXEL_DEPTH_24BPP 130 
#define  LB_PIXEL_DEPTH_30BPP 129 
#define  LB_PIXEL_DEPTH_36BPP 128 

__attribute__((used)) static int tl_lb_bpp_to_int(enum lb_pixel_depth depth)
{
	switch (depth) {
	case LB_PIXEL_DEPTH_18BPP:
		return 18;
	case LB_PIXEL_DEPTH_24BPP:
		return 24;
	case LB_PIXEL_DEPTH_30BPP:
		return 30;
	case LB_PIXEL_DEPTH_36BPP:
		return 36;
	default:
		return 30;
	}
}