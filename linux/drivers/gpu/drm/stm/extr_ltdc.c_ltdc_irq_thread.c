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
struct ltdc_device {int irq_status; int error_status; int /*<<< orphan*/  err_lock; } ;
struct drm_device {struct ltdc_device* dev_private; } ;
struct drm_crtc {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int ISR_FUIF ; 
 int ISR_LIF ; 
 int ISR_TERRIF ; 
 struct drm_crtc* drm_crtc_from_index (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (struct drm_crtc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ltdc_irq_thread(int irq, void *arg)
{
	struct drm_device *ddev = arg;
	struct ltdc_device *ldev = ddev->dev_private;
	struct drm_crtc *crtc = drm_crtc_from_index(ddev, 0);

	/* Line IRQ : trigger the vblank event */
	if (ldev->irq_status & ISR_LIF)
		drm_crtc_handle_vblank(crtc);

	/* Save FIFO Underrun & Transfer Error status */
	mutex_lock(&ldev->err_lock);
	if (ldev->irq_status & ISR_FUIF)
		ldev->error_status |= ISR_FUIF;
	if (ldev->irq_status & ISR_TERRIF)
		ldev->error_status |= ISR_TERRIF;
	mutex_unlock(&ldev->err_lock);

	return IRQ_HANDLED;
}