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
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; } ;
struct ov5695_mode {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ov5695_mode const*) ; 
 int ov5695_get_reso_dist (struct ov5695_mode const*,struct v4l2_mbus_framefmt*) ; 
 struct ov5695_mode const* supported_modes ; 

__attribute__((used)) static const struct ov5695_mode *
ov5695_find_best_fit(struct v4l2_subdev_format *fmt)
{
	struct v4l2_mbus_framefmt *framefmt = &fmt->format;
	int dist;
	int cur_best_fit = 0;
	int cur_best_fit_dist = -1;
	int i;

	for (i = 0; i < ARRAY_SIZE(supported_modes); i++) {
		dist = ov5695_get_reso_dist(&supported_modes[i], framefmt);
		if (cur_best_fit_dist == -1 || dist < cur_best_fit_dist) {
			cur_best_fit_dist = dist;
			cur_best_fit = i;
		}
	}

	return &supported_modes[cur_best_fit];
}