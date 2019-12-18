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
struct v4l2_mbus_config {unsigned long flags; } ;
struct soc_camera_subdev_desc {int flags; } ;

/* Variables and functions */
 int SOCAM_SENSOR_INVERT_HSYNC ; 
 int SOCAM_SENSOR_INVERT_PCLK ; 
 int SOCAM_SENSOR_INVERT_VSYNC ; 
 unsigned long V4L2_MBUS_HSYNC_ACTIVE_HIGH ; 
 unsigned long V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 unsigned long V4L2_MBUS_PCLK_SAMPLE_FALLING ; 
 unsigned long V4L2_MBUS_PCLK_SAMPLE_RISING ; 
 unsigned long V4L2_MBUS_VSYNC_ACTIVE_HIGH ; 
 unsigned long V4L2_MBUS_VSYNC_ACTIVE_LOW ; 

unsigned long soc_camera_apply_board_flags(struct soc_camera_subdev_desc *ssdd,
					   const struct v4l2_mbus_config *cfg)
{
	unsigned long f, flags = cfg->flags;

	/* If only one of the two polarities is supported, switch to the opposite */
	if (ssdd->flags & SOCAM_SENSOR_INVERT_HSYNC) {
		f = flags & (V4L2_MBUS_HSYNC_ACTIVE_HIGH | V4L2_MBUS_HSYNC_ACTIVE_LOW);
		if (f == V4L2_MBUS_HSYNC_ACTIVE_HIGH || f == V4L2_MBUS_HSYNC_ACTIVE_LOW)
			flags ^= V4L2_MBUS_HSYNC_ACTIVE_HIGH | V4L2_MBUS_HSYNC_ACTIVE_LOW;
	}

	if (ssdd->flags & SOCAM_SENSOR_INVERT_VSYNC) {
		f = flags & (V4L2_MBUS_VSYNC_ACTIVE_HIGH | V4L2_MBUS_VSYNC_ACTIVE_LOW);
		if (f == V4L2_MBUS_VSYNC_ACTIVE_HIGH || f == V4L2_MBUS_VSYNC_ACTIVE_LOW)
			flags ^= V4L2_MBUS_VSYNC_ACTIVE_HIGH | V4L2_MBUS_VSYNC_ACTIVE_LOW;
	}

	if (ssdd->flags & SOCAM_SENSOR_INVERT_PCLK) {
		f = flags & (V4L2_MBUS_PCLK_SAMPLE_RISING | V4L2_MBUS_PCLK_SAMPLE_FALLING);
		if (f == V4L2_MBUS_PCLK_SAMPLE_RISING || f == V4L2_MBUS_PCLK_SAMPLE_FALLING)
			flags ^= V4L2_MBUS_PCLK_SAMPLE_RISING | V4L2_MBUS_PCLK_SAMPLE_FALLING;
	}

	return flags;
}