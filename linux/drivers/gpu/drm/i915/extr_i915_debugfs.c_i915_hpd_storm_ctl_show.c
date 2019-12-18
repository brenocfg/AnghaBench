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
struct seq_file {struct drm_i915_private* private; } ;
struct i915_hotplug {int /*<<< orphan*/  reenable_work; int /*<<< orphan*/  hpd_storm_threshold; int /*<<< orphan*/  hotplug_work; int /*<<< orphan*/  dig_port_work; } ;
struct drm_i915_private {struct i915_hotplug hotplug; } ;

/* Variables and functions */
 int /*<<< orphan*/  delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_synchronize_irq (struct drm_i915_private*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_hpd_storm_ctl_show(struct seq_file *m, void *data)
{
	struct drm_i915_private *dev_priv = m->private;
	struct i915_hotplug *hotplug = &dev_priv->hotplug;

	/* Synchronize with everything first in case there's been an HPD
	 * storm, but we haven't finished handling it in the kernel yet
	 */
	intel_synchronize_irq(dev_priv);
	flush_work(&dev_priv->hotplug.dig_port_work);
	flush_delayed_work(&dev_priv->hotplug.hotplug_work);

	seq_printf(m, "Threshold: %d\n", hotplug->hpd_storm_threshold);
	seq_printf(m, "Detected: %s\n",
		   yesno(delayed_work_pending(&hotplug->reenable_work)));

	return 0;
}