#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct v4l2_ctrl {int dummy; } ;
struct et8ek8_sensor {int /*<<< orphan*/  pixel_rate; struct v4l2_ctrl* exposure; TYPE_1__* current_reglist; } ;
struct et8ek8_mode {int max_exp; int pixel_clock; int width; int window_width; } ;
struct TYPE_2__ {struct et8ek8_mode mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  __v4l2_ctrl_modify_range (struct v4l2_ctrl*,int,int,int,int) ; 
 int /*<<< orphan*/  __v4l2_ctrl_s_ctrl_int64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void et8ek8_update_controls(struct et8ek8_sensor *sensor)
{
	struct v4l2_ctrl *ctrl;
	struct et8ek8_mode *mode = &sensor->current_reglist->mode;

	u32 min, max, pixel_rate;
	static const int S = 8;

	ctrl = sensor->exposure;

	min = 1;
	max = mode->max_exp;

	/*
	 * Calculate average pixel clock per line. Assume buffers can spread
	 * the data over horizontal blanking time. Rounding upwards.
	 * Formula taken from stock Nokia N900 kernel.
	 */
	pixel_rate = ((mode->pixel_clock + (1 << S) - 1) >> S) + mode->width;
	pixel_rate = mode->window_width * (pixel_rate - 1) / mode->width;

	__v4l2_ctrl_modify_range(ctrl, min, max, min, max);
	__v4l2_ctrl_s_ctrl_int64(sensor->pixel_rate, pixel_rate << S);
}