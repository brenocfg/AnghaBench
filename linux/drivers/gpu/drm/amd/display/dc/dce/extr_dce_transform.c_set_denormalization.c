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
struct dce_transform {int dummy; } ;
typedef  enum dc_color_depth { ____Placeholder_dc_color_depth } dc_color_depth ;

/* Variables and functions */
#define  COLOR_DEPTH_101010 133 
#define  COLOR_DEPTH_121212 132 
#define  COLOR_DEPTH_141414 131 
#define  COLOR_DEPTH_161616 130 
#define  COLOR_DEPTH_666 129 
#define  COLOR_DEPTH_888 128 
 int /*<<< orphan*/  DENORM_CONTROL ; 
 int /*<<< orphan*/  DENORM_MODE ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_denormalization(
	struct dce_transform *xfm_dce,
	enum dc_color_depth depth)
{
	int denorm_mode = 0;

	switch (depth) {
	case COLOR_DEPTH_666:
		/* 63/64 for 6 bit output color depth */
		denorm_mode = 1;
		break;
	case COLOR_DEPTH_888:
		/* Unity for 8 bit output color depth
		 * because prescale is disabled by default */
		denorm_mode = 0;
		break;
	case COLOR_DEPTH_101010:
		/* 1023/1024 for 10 bit output color depth */
		denorm_mode = 3;
		break;
	case COLOR_DEPTH_121212:
		/* 4095/4096 for 12 bit output color depth */
		denorm_mode = 5;
		break;
	case COLOR_DEPTH_141414:
	case COLOR_DEPTH_161616:
	default:
		/* not valid used case! */
		break;
	}

	REG_SET(DENORM_CONTROL, 0, DENORM_MODE, denorm_mode);
}