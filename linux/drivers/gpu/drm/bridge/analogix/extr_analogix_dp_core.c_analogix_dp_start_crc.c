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
struct drm_connector {TYPE_1__* state; int /*<<< orphan*/  name; } ;
struct analogix_dp_device {int /*<<< orphan*/  aux; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int drm_dp_start_crc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct analogix_dp_device* to_dp (struct drm_connector*) ; 

int analogix_dp_start_crc(struct drm_connector *connector)
{
	struct analogix_dp_device *dp = to_dp(connector);

	if (!connector->state->crtc) {
		DRM_ERROR("Connector %s doesn't currently have a CRTC.\n",
			  connector->name);
		return -EINVAL;
	}

	return drm_dp_start_crc(&dp->aux, connector->state->crtc);
}