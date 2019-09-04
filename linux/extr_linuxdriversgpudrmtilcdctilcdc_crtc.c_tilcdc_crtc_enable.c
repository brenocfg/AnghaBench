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
struct tilcdc_crtc {int enabled; int /*<<< orphan*/  enable_lock; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  last_vblank; scalar_t__ shutdown; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_ONLY ; 
 int /*<<< orphan*/  LCDC_DMA_CTRL_REG ; 
 int /*<<< orphan*/  LCDC_DUAL_FRAME_BUFFER_ENABLE ; 
 int /*<<< orphan*/  LCDC_PALETTE_LOAD_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCDC_PALETTE_LOAD_MODE_MASK ; 
 int /*<<< orphan*/  LCDC_RASTER_CTRL_REG ; 
 int /*<<< orphan*/  LCDC_RASTER_ENABLE ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tilcdc_clear (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tilcdc_crtc_enable_irqs (struct drm_device*) ; 
 int /*<<< orphan*/  tilcdc_crtc_set_mode (struct drm_crtc*) ; 
 int /*<<< orphan*/  tilcdc_set (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tilcdc_write_mask (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tilcdc_crtc* to_tilcdc_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void tilcdc_crtc_enable(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	unsigned long flags;

	mutex_lock(&tilcdc_crtc->enable_lock);
	if (tilcdc_crtc->enabled || tilcdc_crtc->shutdown) {
		mutex_unlock(&tilcdc_crtc->enable_lock);
		return;
	}

	pm_runtime_get_sync(dev->dev);

	reset(crtc);

	tilcdc_crtc_set_mode(crtc);

	tilcdc_crtc_enable_irqs(dev);

	tilcdc_clear(dev, LCDC_DMA_CTRL_REG, LCDC_DUAL_FRAME_BUFFER_ENABLE);
	tilcdc_write_mask(dev, LCDC_RASTER_CTRL_REG,
			  LCDC_PALETTE_LOAD_MODE(DATA_ONLY),
			  LCDC_PALETTE_LOAD_MODE_MASK);

	/* There is no real chance for a race here as the time stamp
	 * is taken before the raster DMA is started. The spin-lock is
	 * taken to have a memory barrier after taking the time-stamp
	 * and to avoid a context switch between taking the stamp and
	 * enabling the raster.
	 */
	spin_lock_irqsave(&tilcdc_crtc->irq_lock, flags);
	tilcdc_crtc->last_vblank = ktime_get();
	tilcdc_set(dev, LCDC_RASTER_CTRL_REG, LCDC_RASTER_ENABLE);
	spin_unlock_irqrestore(&tilcdc_crtc->irq_lock, flags);

	drm_crtc_vblank_on(crtc);

	tilcdc_crtc->enabled = true;
	mutex_unlock(&tilcdc_crtc->enable_lock);
}