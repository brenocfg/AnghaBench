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
typedef  int /*<<< orphan*/  u16 ;
struct seq_file {struct drm_i915_private* private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * spr_latency; int /*<<< orphan*/ * skl_latency; } ;
struct drm_i915_private {TYPE_1__ wm; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  wm_latency_show (struct seq_file*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int spr_wm_latency_show(struct seq_file *m, void *data)
{
	struct drm_i915_private *dev_priv = m->private;
	const u16 *latencies;

	if (INTEL_GEN(dev_priv) >= 9)
		latencies = dev_priv->wm.skl_latency;
	else
		latencies = dev_priv->wm.spr_latency;

	wm_latency_show(m, latencies);

	return 0;
}