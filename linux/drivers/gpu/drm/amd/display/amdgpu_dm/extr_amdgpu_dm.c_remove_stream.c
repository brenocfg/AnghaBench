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
struct dc_stream_state {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_crtc {int otg_inst; int enabled; } ;

/* Variables and functions */

__attribute__((used)) static void remove_stream(struct amdgpu_device *adev,
			  struct amdgpu_crtc *acrtc,
			  struct dc_stream_state *stream)
{
	/* this is the update mode case */

	acrtc->otg_inst = -1;
	acrtc->enabled = false;
}