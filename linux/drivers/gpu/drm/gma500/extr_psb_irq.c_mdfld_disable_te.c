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
struct drm_psb_private {int /*<<< orphan*/  irqmask_lock; int /*<<< orphan*/  dsr_enable; } ;
struct drm_device {scalar_t__ dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE_TE_ENABLE ; 
 int /*<<< orphan*/  mid_disable_pipe_event (struct drm_psb_private*,int) ; 
 int /*<<< orphan*/  psb_disable_pipestat (struct drm_psb_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void mdfld_disable_te(struct drm_device *dev, int pipe)
{
	struct drm_psb_private *dev_priv =
		(struct drm_psb_private *) dev->dev_private;
	unsigned long irqflags;

	if (!dev_priv->dsr_enable)
		return;

	spin_lock_irqsave(&dev_priv->irqmask_lock, irqflags);

	mid_disable_pipe_event(dev_priv, pipe);
	psb_disable_pipestat(dev_priv, pipe, PIPE_TE_ENABLE);

	spin_unlock_irqrestore(&dev_priv->irqmask_lock, irqflags);
}