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
struct mtk_drm_private {TYPE_1__* dma_dev; scalar_t__ dma_parms_allocated; } ;
struct drm_device {int /*<<< orphan*/  dev; struct mtk_drm_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dma_parms; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_unbind_all (int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  drm_atomic_helper_shutdown (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 

__attribute__((used)) static void mtk_drm_kms_deinit(struct drm_device *drm)
{
	struct mtk_drm_private *private = drm->dev_private;

	drm_kms_helper_poll_fini(drm);
	drm_atomic_helper_shutdown(drm);

	if (private->dma_parms_allocated)
		private->dma_dev->dma_parms = NULL;

	component_unbind_all(drm->dev, drm);
	drm_mode_config_cleanup(drm);
}