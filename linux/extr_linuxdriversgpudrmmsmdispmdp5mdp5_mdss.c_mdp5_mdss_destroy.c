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
struct msm_drm_private {int /*<<< orphan*/  mdss; } ;
struct TYPE_2__ {int /*<<< orphan*/ * domain; } ;
struct mdp5_mdss {int /*<<< orphan*/  vdd; TYPE_1__ irqcontroller; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 struct mdp5_mdss* to_mdp5_mdss (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdp5_mdss_destroy(struct drm_device *dev)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct mdp5_mdss *mdp5_mdss = to_mdp5_mdss(priv->mdss);

	if (!mdp5_mdss)
		return;

	irq_domain_remove(mdp5_mdss->irqcontroller.domain);
	mdp5_mdss->irqcontroller.domain = NULL;

	regulator_disable(mdp5_mdss->vdd);

	pm_runtime_disable(dev->dev);
}