#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u8 ;
struct msm_dsi_host {TYPE_2__* tx_gem_obj; int /*<<< orphan*/  tx_size; struct drm_device* dev; } ;
struct msm_drm_private {TYPE_1__* kms; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int /*<<< orphan*/  aspace; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSM_BO_UNCACHED ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msm_gem_kernel_new (struct drm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_object_set_name (TYPE_2__*,char*) ; 

int dsi_tx_buf_alloc_6g(struct msm_dsi_host *msm_host, int size)
{
	struct drm_device *dev = msm_host->dev;
	struct msm_drm_private *priv = dev->dev_private;
	uint64_t iova;
	u8 *data;

	data = msm_gem_kernel_new(dev, size, MSM_BO_UNCACHED,
					priv->kms->aspace,
					&msm_host->tx_gem_obj, &iova);

	if (IS_ERR(data)) {
		msm_host->tx_gem_obj = NULL;
		return PTR_ERR(data);
	}

	msm_gem_object_set_name(msm_host->tx_gem_obj, "tx_gem");

	msm_host->tx_size = msm_host->tx_gem_obj->size;

	return 0;
}