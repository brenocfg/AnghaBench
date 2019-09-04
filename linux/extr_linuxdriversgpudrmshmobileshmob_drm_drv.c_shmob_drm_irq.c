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
typedef  int u32 ;
struct shmob_drm_device {int /*<<< orphan*/  crtc; int /*<<< orphan*/  irq_lock; } ;
struct drm_device {struct shmob_drm_device* dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  LDINTR ; 
 int LDINTR_STATUS_MASK ; 
 int LDINTR_VES ; 
 int /*<<< orphan*/  drm_handle_vblank (struct drm_device*,int /*<<< orphan*/ ) ; 
 int lcdc_read (struct shmob_drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (struct shmob_drm_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  shmob_drm_crtc_finish_page_flip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t shmob_drm_irq(int irq, void *arg)
{
	struct drm_device *dev = arg;
	struct shmob_drm_device *sdev = dev->dev_private;
	unsigned long flags;
	u32 status;

	/* Acknowledge interrupts. Putting interrupt enable and interrupt flag
	 * bits in the same register is really brain-dead design and requires
	 * taking a spinlock.
	 */
	spin_lock_irqsave(&sdev->irq_lock, flags);
	status = lcdc_read(sdev, LDINTR);
	lcdc_write(sdev, LDINTR, status ^ LDINTR_STATUS_MASK);
	spin_unlock_irqrestore(&sdev->irq_lock, flags);

	if (status & LDINTR_VES) {
		drm_handle_vblank(dev, 0);
		shmob_drm_crtc_finish_page_flip(&sdev->crtc);
	}

	return IRQ_HANDLED;
}