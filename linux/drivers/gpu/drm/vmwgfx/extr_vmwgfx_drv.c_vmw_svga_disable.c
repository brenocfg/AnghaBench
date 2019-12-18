#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* man; } ;
struct vmw_private {int /*<<< orphan*/  reservation_sem; int /*<<< orphan*/  svga_lock; TYPE_2__ bdev; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int use_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  SVGA_REG_ENABLE ; 
 int SVGA_REG_ENABLE_ENABLE ; 
 int SVGA_REG_ENABLE_HIDE ; 
 size_t TTM_PL_VRAM ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ttm_bo_evict_mm (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  ttm_write_lock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ttm_write_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_kms_lost_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_write (struct vmw_private*,int /*<<< orphan*/ ,int) ; 

void vmw_svga_disable(struct vmw_private *dev_priv)
{
	/*
	 * Disabling SVGA will turn off device modesetting capabilities, so
	 * notify KMS about that so that it doesn't cache atomic state that
	 * isn't valid anymore, for example crtcs turned on.
	 * Strictly we'd want to do this under the SVGA lock (or an SVGA mutex),
	 * but vmw_kms_lost_device() takes the reservation sem and thus we'll
	 * end up with lock order reversal. Thus, a master may actually perform
	 * a new modeset just after we call vmw_kms_lost_device() and race with
	 * vmw_svga_disable(), but that should at worst cause atomic KMS state
	 * to be inconsistent with the device, causing modesetting problems.
	 *
	 */
	vmw_kms_lost_device(dev_priv->dev);
	ttm_write_lock(&dev_priv->reservation_sem, false);
	spin_lock(&dev_priv->svga_lock);
	if (dev_priv->bdev.man[TTM_PL_VRAM].use_type) {
		dev_priv->bdev.man[TTM_PL_VRAM].use_type = false;
		spin_unlock(&dev_priv->svga_lock);
		if (ttm_bo_evict_mm(&dev_priv->bdev, TTM_PL_VRAM))
			DRM_ERROR("Failed evicting VRAM buffers.\n");
		vmw_write(dev_priv, SVGA_REG_ENABLE,
			  SVGA_REG_ENABLE_HIDE |
			  SVGA_REG_ENABLE_ENABLE);
	} else
		spin_unlock(&dev_priv->svga_lock);
	ttm_write_unlock(&dev_priv->reservation_sem);
}