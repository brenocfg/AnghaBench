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
typedef  scalar_t__ uint8_t ;
struct mod_freesync_params {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {struct amdgpu_device* dev_private; } ;
struct dc_stream_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  freesync_module; int /*<<< orphan*/  dc; } ;
struct amdgpu_device {TYPE_1__ dm; } ;

/* Variables and functions */
 scalar_t__ dc_get_current_stream_count (int /*<<< orphan*/ ) ; 
 struct dc_stream_state* dc_get_stream_at_index (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mod_freesync_update_state (int /*<<< orphan*/ ,struct dc_stream_state**,int,struct mod_freesync_params*) ; 

__attribute__((used)) static int amdgpu_notify_freesync(struct drm_device *dev, void *data,
				struct drm_file *filp)
{
	struct mod_freesync_params freesync_params;
	uint8_t num_streams;
	uint8_t i;

	struct amdgpu_device *adev = dev->dev_private;
	int r = 0;

	/* Get freesync enable flag from DRM */

	num_streams = dc_get_current_stream_count(adev->dm.dc);

	for (i = 0; i < num_streams; i++) {
		struct dc_stream_state *stream;
		stream = dc_get_stream_at_index(adev->dm.dc, i);

		mod_freesync_update_state(adev->dm.freesync_module,
					  &stream, 1, &freesync_params);
	}

	return r;
}