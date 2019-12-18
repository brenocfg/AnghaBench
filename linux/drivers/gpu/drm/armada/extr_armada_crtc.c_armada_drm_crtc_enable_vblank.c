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
struct drm_crtc {int dummy; } ;
struct armada_crtc {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  VSYNC_IRQ_ENA ; 
 int /*<<< orphan*/  armada_drm_crtc_enable_irq (struct armada_crtc*,int /*<<< orphan*/ ) ; 
 struct armada_crtc* drm_to_armada_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int armada_drm_crtc_enable_vblank(struct drm_crtc *crtc)
{
	struct armada_crtc *dcrtc = drm_to_armada_crtc(crtc);
	unsigned long flags;

	spin_lock_irqsave(&dcrtc->irq_lock, flags);
	armada_drm_crtc_enable_irq(dcrtc, VSYNC_IRQ_ENA);
	spin_unlock_irqrestore(&dcrtc->irq_lock, flags);
	return 0;
}