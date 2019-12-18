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
struct TYPE_2__ {int irq; int /*<<< orphan*/ * platdev; } ;
struct drm_i915_private {TYPE_1__ lpe_audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLV_AUD_CHICKEN_BIT_REG ; 
 int /*<<< orphan*/  VLV_CHICKEN_BIT_DBG_ENABLE ; 
 int irq_alloc_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_free_desc (int) ; 
 int lpe_audio_irq_init (struct drm_i915_private*) ; 
 int /*<<< orphan*/ * lpe_audio_platdev_create (struct drm_i915_private*) ; 

__attribute__((used)) static int lpe_audio_setup(struct drm_i915_private *dev_priv)
{
	int ret;

	dev_priv->lpe_audio.irq = irq_alloc_desc(0);
	if (dev_priv->lpe_audio.irq < 0) {
		DRM_ERROR("Failed to allocate IRQ desc: %d\n",
			dev_priv->lpe_audio.irq);
		ret = dev_priv->lpe_audio.irq;
		goto err;
	}

	DRM_DEBUG("irq = %d\n", dev_priv->lpe_audio.irq);

	ret = lpe_audio_irq_init(dev_priv);

	if (ret) {
		DRM_ERROR("Failed to initialize irqchip for lpe audio: %d\n",
			ret);
		goto err_free_irq;
	}

	dev_priv->lpe_audio.platdev = lpe_audio_platdev_create(dev_priv);

	if (IS_ERR(dev_priv->lpe_audio.platdev)) {
		ret = PTR_ERR(dev_priv->lpe_audio.platdev);
		DRM_ERROR("Failed to create lpe audio platform device: %d\n",
			ret);
		goto err_free_irq;
	}

	/* enable chicken bit; at least this is required for Dell Wyse 3040
	 * with DP outputs (but only sometimes by some reason!)
	 */
	I915_WRITE(VLV_AUD_CHICKEN_BIT_REG, VLV_CHICKEN_BIT_DBG_ENABLE);

	return 0;
err_free_irq:
	irq_free_desc(dev_priv->lpe_audio.irq);
err:
	dev_priv->lpe_audio.irq = -1;
	dev_priv->lpe_audio.platdev = NULL;
	return ret;
}