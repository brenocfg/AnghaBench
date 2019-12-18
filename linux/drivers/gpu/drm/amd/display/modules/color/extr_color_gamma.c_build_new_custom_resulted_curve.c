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
typedef  size_t uint32_t ;
struct dc_transfer_func_distributed_points {void** blue; void** green; void** red; } ;

/* Variables and functions */
 void* dc_fixpt_clamp (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_fixpt_one ; 
 int /*<<< orphan*/  dc_fixpt_zero ; 

__attribute__((used)) static void build_new_custom_resulted_curve(
	uint32_t hw_points_num,
	struct dc_transfer_func_distributed_points *tf_pts)
{
	uint32_t i;

	i = 0;

	while (i != hw_points_num + 1) {
		tf_pts->red[i] = dc_fixpt_clamp(
			tf_pts->red[i], dc_fixpt_zero,
			dc_fixpt_one);
		tf_pts->green[i] = dc_fixpt_clamp(
			tf_pts->green[i], dc_fixpt_zero,
			dc_fixpt_one);
		tf_pts->blue[i] = dc_fixpt_clamp(
			tf_pts->blue[i], dc_fixpt_zero,
			dc_fixpt_one);

		++i;
	}
}