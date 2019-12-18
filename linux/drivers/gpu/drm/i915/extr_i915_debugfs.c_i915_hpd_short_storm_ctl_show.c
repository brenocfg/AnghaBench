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
struct seq_file {struct drm_i915_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  hpd_short_storm_enabled; } ;
struct drm_i915_private {TYPE_1__ hotplug; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yesno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_hpd_short_storm_ctl_show(struct seq_file *m, void *data)
{
	struct drm_i915_private *dev_priv = m->private;

	seq_printf(m, "Enabled: %s\n",
		   yesno(dev_priv->hotplug.hpd_short_storm_enabled));

	return 0;
}