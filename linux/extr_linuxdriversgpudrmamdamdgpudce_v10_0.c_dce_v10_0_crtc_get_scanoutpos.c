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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int num_crtc; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RREG32 (scalar_t__) ; 
 scalar_t__* crtc_offsets ; 
 scalar_t__ mmCRTC_STATUS_POSITION ; 
 scalar_t__ mmCRTC_V_BLANK_START_END ; 

__attribute__((used)) static int dce_v10_0_crtc_get_scanoutpos(struct amdgpu_device *adev, int crtc,
					u32 *vbl, u32 *position)
{
	if ((crtc < 0) || (crtc >= adev->mode_info.num_crtc))
		return -EINVAL;

	*vbl = RREG32(mmCRTC_V_BLANK_START_END + crtc_offsets[crtc]);
	*position = RREG32(mmCRTC_STATUS_POSITION + crtc_offsets[crtc]);

	return 0;
}