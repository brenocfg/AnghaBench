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
struct TYPE_2__ {struct drm_device* dev; } ;
struct psb_framebuffer {TYPE_1__ base; } ;
struct psb_fbdev {struct psb_framebuffer pfb; } ;
struct fb_info {struct psb_fbdev* par; } ;
struct drm_psb_private {int /*<<< orphan*/  lock_2d; } ;
struct drm_device {struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  PSB_CR_2D_BLIT_STATUS ; 
 int /*<<< orphan*/  PSB_CR_2D_SOCIF ; 
 int PSB_RSGX32 (int /*<<< orphan*/ ) ; 
 int _PSB_C2B_STATUS_BUSY ; 
 int _PSB_C2_SOCIF_EMPTY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  time_after_eq (unsigned long,unsigned long) ; 

int psbfb_sync(struct fb_info *info)
{
	struct psb_fbdev *fbdev = info->par;
	struct psb_framebuffer *psbfb = &fbdev->pfb;
	struct drm_device *dev = psbfb->base.dev;
	struct drm_psb_private *dev_priv = dev->dev_private;
	unsigned long _end = jiffies + HZ;
	int busy = 0;
	unsigned long flags;

	spin_lock_irqsave(&dev_priv->lock_2d, flags);
	/*
	 * First idle the 2D engine.
	 */

	if ((PSB_RSGX32(PSB_CR_2D_SOCIF) == _PSB_C2_SOCIF_EMPTY) &&
	    ((PSB_RSGX32(PSB_CR_2D_BLIT_STATUS) & _PSB_C2B_STATUS_BUSY) == 0))
		goto out;

	do {
		busy = (PSB_RSGX32(PSB_CR_2D_SOCIF) != _PSB_C2_SOCIF_EMPTY);
		cpu_relax();
	} while (busy && !time_after_eq(jiffies, _end));

	if (busy)
		busy = (PSB_RSGX32(PSB_CR_2D_SOCIF) != _PSB_C2_SOCIF_EMPTY);
	if (busy)
		goto out;

	do {
		busy = ((PSB_RSGX32(PSB_CR_2D_BLIT_STATUS) &
						_PSB_C2B_STATUS_BUSY) != 0);
		cpu_relax();
	} while (busy && !time_after_eq(jiffies, _end));
	if (busy)
		busy = ((PSB_RSGX32(PSB_CR_2D_BLIT_STATUS) &
					_PSB_C2B_STATUS_BUSY) != 0);

out:
	spin_unlock_irqrestore(&dev_priv->lock_2d, flags);
	return (busy) ? -EBUSY : 0;
}