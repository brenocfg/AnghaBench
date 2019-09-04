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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  format; scalar_t__ pad; } ;
struct v4l2_subdev {int dummy; } ;
struct adv7183 {int /*<<< orphan*/  fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 struct adv7183* to_adv7183 (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7183_get_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct adv7183 *decoder = to_adv7183(sd);

	if (format->pad)
		return -EINVAL;

	format->format = decoder->fmt;
	return 0;
}