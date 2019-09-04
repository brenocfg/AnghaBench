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
struct dc_stream_state {int dummy; } ;
struct TYPE_2__ {scalar_t__ freesync_module; } ;
struct amdgpu_device {TYPE_1__ dm; } ;
struct amdgpu_crtc {int otg_inst; int enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_freesync_remove_stream (scalar_t__,struct dc_stream_state*) ; 

__attribute__((used)) static void remove_stream(struct amdgpu_device *adev,
			  struct amdgpu_crtc *acrtc,
			  struct dc_stream_state *stream)
{
	/* this is the update mode case */
	if (adev->dm.freesync_module)
		mod_freesync_remove_stream(adev->dm.freesync_module, stream);

	acrtc->otg_inst = -1;
	acrtc->enabled = false;
}