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
struct msm_dsi_host {int /*<<< orphan*/  tx_buf_paddr; int /*<<< orphan*/  tx_buf; int /*<<< orphan*/  tx_size; int /*<<< orphan*/ * tx_gem_obj; struct drm_device* dev; } ;
struct msm_drm_private {TYPE_1__* kms; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  aspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_unpin_iova (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsi_tx_buf_free(struct msm_dsi_host *msm_host)
{
	struct drm_device *dev = msm_host->dev;
	struct msm_drm_private *priv;

	/*
	 * This is possible if we're tearing down before we've had a chance to
	 * fully initialize. A very real possibility if our probe is deferred,
	 * in which case we'll hit msm_dsi_host_destroy() without having run
	 * through the dsi_tx_buf_alloc().
	 */
	if (!dev)
		return;

	priv = dev->dev_private;
	if (msm_host->tx_gem_obj) {
		msm_gem_unpin_iova(msm_host->tx_gem_obj, priv->kms->aspace);
		drm_gem_object_put_unlocked(msm_host->tx_gem_obj);
		msm_host->tx_gem_obj = NULL;
	}

	if (msm_host->tx_buf)
		dma_free_coherent(dev->dev, msm_host->tx_size, msm_host->tx_buf,
			msm_host->tx_buf_paddr);
}