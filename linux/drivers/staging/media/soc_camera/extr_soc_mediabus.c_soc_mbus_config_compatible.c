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
struct v4l2_mbus_config {unsigned int flags; int type; } ;

/* Variables and functions */
 unsigned int EINVAL ; 
#define  V4L2_MBUS_BT656 130 
 unsigned long V4L2_MBUS_CSI2_CONTINUOUS_CLOCK ; 
#define  V4L2_MBUS_CSI2_DPHY 129 
 unsigned long V4L2_MBUS_CSI2_LANES ; 
 unsigned long V4L2_MBUS_CSI2_NONCONTINUOUS_CLOCK ; 
 unsigned long V4L2_MBUS_DATA_ACTIVE_HIGH ; 
 unsigned long V4L2_MBUS_DATA_ACTIVE_LOW ; 
 unsigned long V4L2_MBUS_HSYNC_ACTIVE_HIGH ; 
 unsigned long V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 unsigned long V4L2_MBUS_MASTER ; 
#define  V4L2_MBUS_PARALLEL 128 
 unsigned long V4L2_MBUS_PCLK_SAMPLE_FALLING ; 
 unsigned long V4L2_MBUS_PCLK_SAMPLE_RISING ; 
 unsigned long V4L2_MBUS_SLAVE ; 
 unsigned long V4L2_MBUS_VSYNC_ACTIVE_HIGH ; 
 unsigned long V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

unsigned int soc_mbus_config_compatible(const struct v4l2_mbus_config *cfg,
					unsigned int flags)
{
	unsigned long common_flags;
	bool hsync = true, vsync = true, pclk, data, mode;
	bool mipi_lanes, mipi_clock;

	common_flags = cfg->flags & flags;

	switch (cfg->type) {
	case V4L2_MBUS_PARALLEL:
		hsync = common_flags & (V4L2_MBUS_HSYNC_ACTIVE_HIGH |
					V4L2_MBUS_HSYNC_ACTIVE_LOW);
		vsync = common_flags & (V4L2_MBUS_VSYNC_ACTIVE_HIGH |
					V4L2_MBUS_VSYNC_ACTIVE_LOW);
		/* fall through */
	case V4L2_MBUS_BT656:
		pclk = common_flags & (V4L2_MBUS_PCLK_SAMPLE_RISING |
				       V4L2_MBUS_PCLK_SAMPLE_FALLING);
		data = common_flags & (V4L2_MBUS_DATA_ACTIVE_HIGH |
				       V4L2_MBUS_DATA_ACTIVE_LOW);
		mode = common_flags & (V4L2_MBUS_MASTER | V4L2_MBUS_SLAVE);
		return (!hsync || !vsync || !pclk || !data || !mode) ?
			0 : common_flags;
	case V4L2_MBUS_CSI2_DPHY:
		mipi_lanes = common_flags & V4L2_MBUS_CSI2_LANES;
		mipi_clock = common_flags & (V4L2_MBUS_CSI2_NONCONTINUOUS_CLOCK |
					     V4L2_MBUS_CSI2_CONTINUOUS_CLOCK);
		return (!mipi_lanes || !mipi_clock) ? 0 : common_flags;
	default:
		WARN_ON(1);
		return -EINVAL;
	}
	return 0;
}