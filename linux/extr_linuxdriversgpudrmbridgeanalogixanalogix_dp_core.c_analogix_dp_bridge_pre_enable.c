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
struct drm_bridge {struct analogix_dp_device* driver_private; } ;
struct analogix_dp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int analogix_dp_prepare_panel (struct analogix_dp_device*,int,int) ; 

__attribute__((used)) static void analogix_dp_bridge_pre_enable(struct drm_bridge *bridge)
{
	struct analogix_dp_device *dp = bridge->driver_private;
	int ret;

	ret = analogix_dp_prepare_panel(dp, true, true);
	if (ret)
		DRM_ERROR("failed to setup the panel ret = %d\n", ret);
}