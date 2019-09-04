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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int) ; 
 scalar_t__ EVERGREEN_DP_STEER_FIFO ; 
 unsigned int EVERGREEN_DP_STEER_FIFO_RESET ; 
 scalar_t__ EVERGREEN_DP_VID_STREAM_CNTL ; 
 unsigned int EVERGREEN_DP_VID_STREAM_CNTL_ENABLE ; 
 unsigned int EVERGREEN_DP_VID_STREAM_STATUS ; 
 unsigned int RREG32 (scalar_t__) ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,unsigned int) ; 
 scalar_t__* evergreen_dp_offsets ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void evergreen_blank_dp_output(struct radeon_device *rdev,
				      unsigned dig_fe)
{
	unsigned stream_ctrl;
	unsigned fifo_ctrl;
	unsigned counter = 0;

	if (dig_fe >= ARRAY_SIZE(evergreen_dp_offsets)) {
		DRM_ERROR("invalid dig_fe %d\n", dig_fe);
		return;
	}

	stream_ctrl = RREG32(EVERGREEN_DP_VID_STREAM_CNTL +
			     evergreen_dp_offsets[dig_fe]);
	if (!(stream_ctrl & EVERGREEN_DP_VID_STREAM_CNTL_ENABLE)) {
		DRM_ERROR("dig %d , should be enable\n", dig_fe);
		return;
	}

	stream_ctrl &=~EVERGREEN_DP_VID_STREAM_CNTL_ENABLE;
	WREG32(EVERGREEN_DP_VID_STREAM_CNTL +
	       evergreen_dp_offsets[dig_fe], stream_ctrl);

	stream_ctrl = RREG32(EVERGREEN_DP_VID_STREAM_CNTL +
			     evergreen_dp_offsets[dig_fe]);
	while (counter < 32 && stream_ctrl & EVERGREEN_DP_VID_STREAM_STATUS) {
		msleep(1);
		counter++;
		stream_ctrl = RREG32(EVERGREEN_DP_VID_STREAM_CNTL +
				     evergreen_dp_offsets[dig_fe]);
	}
	if (counter >= 32 )
		DRM_ERROR("counter exceeds %d\n", counter);

	fifo_ctrl = RREG32(EVERGREEN_DP_STEER_FIFO + evergreen_dp_offsets[dig_fe]);
	fifo_ctrl |= EVERGREEN_DP_STEER_FIFO_RESET;
	WREG32(EVERGREEN_DP_STEER_FIFO + evergreen_dp_offsets[dig_fe], fifo_ctrl);

}