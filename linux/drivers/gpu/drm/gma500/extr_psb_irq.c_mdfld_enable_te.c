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
typedef  int uint32_t ;
struct drm_psb_private {int /*<<< orphan*/  irqmask_lock; } ;
struct drm_device {scalar_t__ dev_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int PIPEACONF_ENABLE ; 
 int /*<<< orphan*/  PIPE_TE_ENABLE ; 
 int REG_READ (int) ; 
 scalar_t__ gma_power_begin (struct drm_device*,int) ; 
 int /*<<< orphan*/  gma_power_end (struct drm_device*) ; 
 int /*<<< orphan*/  mid_enable_pipe_event (struct drm_psb_private*,int) ; 
 int mid_pipeconf (int) ; 
 int /*<<< orphan*/  psb_enable_pipestat (struct drm_psb_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int mdfld_enable_te(struct drm_device *dev, int pipe)
{
	struct drm_psb_private *dev_priv =
		(struct drm_psb_private *) dev->dev_private;
	unsigned long irqflags;
	uint32_t reg_val = 0;
	uint32_t pipeconf_reg = mid_pipeconf(pipe);

	if (gma_power_begin(dev, false)) {
		reg_val = REG_READ(pipeconf_reg);
		gma_power_end(dev);
	}

	if (!(reg_val & PIPEACONF_ENABLE))
		return -EINVAL;

	spin_lock_irqsave(&dev_priv->irqmask_lock, irqflags);

	mid_enable_pipe_event(dev_priv, pipe);
	psb_enable_pipestat(dev_priv, pipe, PIPE_TE_ENABLE);

	spin_unlock_irqrestore(&dev_priv->irqmask_lock, irqflags);

	return 0;
}