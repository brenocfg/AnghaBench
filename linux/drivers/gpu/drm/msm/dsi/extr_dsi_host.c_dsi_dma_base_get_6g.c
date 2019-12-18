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
typedef  int /*<<< orphan*/  uint64_t ;
struct msm_dsi_host {int /*<<< orphan*/  tx_gem_obj; struct drm_device* dev; } ;
struct msm_drm_private {TYPE_1__* kms; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  aspace; } ;

/* Variables and functions */
 int EINVAL ; 
 int msm_gem_get_and_pin_iova (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dsi_dma_base_get_6g(struct msm_dsi_host *msm_host, uint64_t *dma_base)
{
	struct drm_device *dev = msm_host->dev;
	struct msm_drm_private *priv = dev->dev_private;

	if (!dma_base)
		return -EINVAL;

	return msm_gem_get_and_pin_iova(msm_host->tx_gem_obj,
				priv->kms->aspace, dma_base);
}