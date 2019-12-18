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
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_connector_unregister_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_crtc_unregister_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_encoder_unregister_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_plane_unregister_all (struct drm_device*) ; 

void drm_modeset_unregister_all(struct drm_device *dev)
{
	drm_connector_unregister_all(dev);
	drm_encoder_unregister_all(dev);
	drm_crtc_unregister_all(dev);
	drm_plane_unregister_all(dev);
}