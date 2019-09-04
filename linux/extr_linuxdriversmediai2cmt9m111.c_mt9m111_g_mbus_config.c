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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_config {int flags; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int V4L2_MBUS_DATA_ACTIVE_HIGH ; 
 int V4L2_MBUS_HSYNC_ACTIVE_HIGH ; 
 int V4L2_MBUS_MASTER ; 
 int /*<<< orphan*/  V4L2_MBUS_PARALLEL ; 
 int V4L2_MBUS_PCLK_SAMPLE_RISING ; 
 int V4L2_MBUS_VSYNC_ACTIVE_HIGH ; 

__attribute__((used)) static int mt9m111_g_mbus_config(struct v4l2_subdev *sd,
				struct v4l2_mbus_config *cfg)
{
	cfg->flags = V4L2_MBUS_MASTER | V4L2_MBUS_PCLK_SAMPLE_RISING |
		V4L2_MBUS_HSYNC_ACTIVE_HIGH | V4L2_MBUS_VSYNC_ACTIVE_HIGH |
		V4L2_MBUS_DATA_ACTIVE_HIGH;
	cfg->type = V4L2_MBUS_PARALLEL;

	return 0;
}