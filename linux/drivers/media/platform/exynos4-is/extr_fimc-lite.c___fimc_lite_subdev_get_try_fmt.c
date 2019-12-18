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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;

/* Variables and functions */
 unsigned int FLITE_SD_PAD_SINK ; 
 unsigned int FLITE_SD_PAD_SOURCE_DMA ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,unsigned int) ; 

__attribute__((used)) static struct v4l2_mbus_framefmt *__fimc_lite_subdev_get_try_fmt(
		struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg, unsigned int pad)
{
	if (pad != FLITE_SD_PAD_SINK)
		pad = FLITE_SD_PAD_SOURCE_DMA;

	return v4l2_subdev_get_try_format(sd, cfg, pad);
}