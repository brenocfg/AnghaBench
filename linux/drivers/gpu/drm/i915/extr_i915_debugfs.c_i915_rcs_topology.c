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
struct seq_file {int /*<<< orphan*/  private; } ;
struct drm_printer {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sseu; } ;

/* Variables and functions */
 TYPE_1__* RUNTIME_INFO (struct drm_i915_private*) ; 
 struct drm_printer drm_seq_file_printer (struct seq_file*) ; 
 int /*<<< orphan*/  intel_device_info_dump_topology (int /*<<< orphan*/ *,struct drm_printer*) ; 
 struct drm_i915_private* node_to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_rcs_topology(struct seq_file *m, void *unused)
{
	struct drm_i915_private *dev_priv = node_to_i915(m->private);
	struct drm_printer p = drm_seq_file_printer(m);

	intel_device_info_dump_topology(&RUNTIME_INFO(dev_priv)->sseu, &p);

	return 0;
}