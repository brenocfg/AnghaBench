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
struct shmob_drm_device {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDINTR ; 
 int LDINTR_STATUS_MASK ; 
 int LDINTR_VEE ; 
 int lcdc_read (struct shmob_drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (struct shmob_drm_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void shmob_drm_crtc_enable_vblank(struct shmob_drm_device *sdev,
					 bool enable)
{
	unsigned long flags;
	u32 ldintr;

	/* Be careful not to acknowledge any pending interrupt. */
	spin_lock_irqsave(&sdev->irq_lock, flags);
	ldintr = lcdc_read(sdev, LDINTR) | LDINTR_STATUS_MASK;
	if (enable)
		ldintr |= LDINTR_VEE;
	else
		ldintr &= ~LDINTR_VEE;
	lcdc_write(sdev, LDINTR, ldintr);
	spin_unlock_irqrestore(&sdev->irq_lock, flags);
}