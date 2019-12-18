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
struct msm_kms {int dummy; } ;
struct msm_drm_private {unsigned int num_crtcs; int /*<<< orphan*/ * crtcs; } ;
struct mdp_kms {int dummy; } ;
struct mdp5_kms {struct drm_device* dev; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  REG_MDP5_INTR_CLEAR ; 
 int /*<<< orphan*/  REG_MDP5_INTR_EN ; 
 int /*<<< orphan*/  REG_MDP5_INTR_STATUS ; 
 int /*<<< orphan*/  VERB (char*,int) ; 
 int /*<<< orphan*/  drm_handle_vblank (struct drm_device*,unsigned int) ; 
 int mdp5_crtc_vblank (int /*<<< orphan*/ ) ; 
 int mdp5_read (struct mdp5_kms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_write (struct mdp5_kms*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdp_dispatch_irqs (struct mdp_kms*,int) ; 
 struct mdp5_kms* to_mdp5_kms (struct mdp_kms*) ; 
 struct mdp_kms* to_mdp_kms (struct msm_kms*) ; 

irqreturn_t mdp5_irq(struct msm_kms *kms)
{
	struct mdp_kms *mdp_kms = to_mdp_kms(kms);
	struct mdp5_kms *mdp5_kms = to_mdp5_kms(mdp_kms);
	struct drm_device *dev = mdp5_kms->dev;
	struct msm_drm_private *priv = dev->dev_private;
	unsigned int id;
	uint32_t status, enable;

	enable = mdp5_read(mdp5_kms, REG_MDP5_INTR_EN);
	status = mdp5_read(mdp5_kms, REG_MDP5_INTR_STATUS) & enable;
	mdp5_write(mdp5_kms, REG_MDP5_INTR_CLEAR, status);

	VERB("status=%08x", status);

	mdp_dispatch_irqs(mdp_kms, status);

	for (id = 0; id < priv->num_crtcs; id++)
		if (status & mdp5_crtc_vblank(priv->crtcs[id]))
			drm_handle_vblank(dev, id);

	return IRQ_HANDLED;
}