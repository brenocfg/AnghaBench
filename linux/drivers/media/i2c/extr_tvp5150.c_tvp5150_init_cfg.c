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
typedef  scalar_t__ v4l2_std_id ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct tvp5150 {scalar_t__ norm; scalar_t__ detected_norm; int /*<<< orphan*/  rect; } ;

/* Variables and functions */
 scalar_t__ V4L2_STD_ALL ; 
 struct tvp5150* to_tvp5150 (struct v4l2_subdev*) ; 
 scalar_t__ tvp5150_read_std (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tvp5150_set_default (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tvp5150_init_cfg(struct v4l2_subdev *sd,
			    struct v4l2_subdev_pad_config *cfg)
{
	struct tvp5150 *decoder = to_tvp5150(sd);
	v4l2_std_id std;

	/*
	 * Reset selection to maximum on subdev_open() if autodetection is on
	 * and a standard change is detected.
	 */
	if (decoder->norm == V4L2_STD_ALL) {
		std = tvp5150_read_std(sd);
		if (std != decoder->detected_norm) {
			decoder->detected_norm = std;
			tvp5150_set_default(std, &decoder->rect);
		}
	}

	return 0;
}