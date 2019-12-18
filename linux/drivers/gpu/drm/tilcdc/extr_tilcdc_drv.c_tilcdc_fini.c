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
struct TYPE_2__ {scalar_t__ notifier_call; } ;
struct tilcdc_drm_private {scalar_t__ wq; scalar_t__ mmio; scalar_t__ clk; scalar_t__ is_registered; scalar_t__ crtc; TYPE_1__ freq_transition; } ;
struct drm_device {int /*<<< orphan*/  dev; struct tilcdc_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_TRANSITION_NOTIFIER ; 
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 int /*<<< orphan*/  cpufreq_unregister_notifier (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tilcdc_crtc_shutdown (scalar_t__) ; 

__attribute__((used)) static void tilcdc_fini(struct drm_device *dev)
{
	struct tilcdc_drm_private *priv = dev->dev_private;

#ifdef CONFIG_CPU_FREQ
	if (priv->freq_transition.notifier_call)
		cpufreq_unregister_notifier(&priv->freq_transition,
					    CPUFREQ_TRANSITION_NOTIFIER);
#endif

	if (priv->crtc)
		tilcdc_crtc_shutdown(priv->crtc);

	if (priv->is_registered)
		drm_dev_unregister(dev);

	drm_kms_helper_poll_fini(dev);
	drm_irq_uninstall(dev);
	drm_mode_config_cleanup(dev);

	if (priv->clk)
		clk_put(priv->clk);

	if (priv->mmio)
		iounmap(priv->mmio);

	if (priv->wq) {
		flush_workqueue(priv->wq);
		destroy_workqueue(priv->wq);
	}

	dev->dev_private = NULL;

	pm_runtime_disable(dev->dev);

	drm_dev_put(dev);
}