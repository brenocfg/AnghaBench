#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_file {int dummy; } ;
struct drm_device {TYPE_1__* dev_private; } ;
struct TYPE_4__ {scalar_t__ cce_running; } ;
typedef  TYPE_1__ drm_r128_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_INIT_TEST_WITH_RETURN (TYPE_1__*) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  LOCK_TEST_WITH_RETURN (struct drm_device*,struct drm_file*) ; 
 int /*<<< orphan*/  r128_do_cce_reset (TYPE_1__*) ; 

int r128_cce_reset(struct drm_device *dev, void *data, struct drm_file *file_priv)
{
	drm_r128_private_t *dev_priv = dev->dev_private;
	DRM_DEBUG("\n");

	LOCK_TEST_WITH_RETURN(dev, file_priv);

	DEV_INIT_TEST_WITH_RETURN(dev_priv);

	r128_do_cce_reset(dev_priv);

	/* The CCE is no longer running after an engine reset */
	dev_priv->cce_running = 0;

	return 0;
}