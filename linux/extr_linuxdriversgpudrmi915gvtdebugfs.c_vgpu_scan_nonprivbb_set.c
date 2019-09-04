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
typedef  int u64 ;
struct intel_vgpu {int scan_nonprivbb; int id; TYPE_1__* gvt; } ;
struct intel_engine_cs {int id; } ;
struct drm_i915_private {struct intel_engine_cs** engine; } ;
typedef  enum intel_engine_id { ____Placeholder_intel_engine_id } intel_engine_id ;
struct TYPE_2__ {struct drm_i915_private* dev_priv; } ;

/* Variables and functions */
 int I915_NUM_ENGINES ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 
 int snprintf (char*,int,char*,int) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int
vgpu_scan_nonprivbb_set(void *data, u64 val)
{
	struct intel_vgpu *vgpu = (struct intel_vgpu *)data;
	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;
	enum intel_engine_id id;
	char buf[128], *s;
	int len;

	val &= (1 << I915_NUM_ENGINES) - 1;

	if (vgpu->scan_nonprivbb == val)
		return 0;

	if (!val)
		goto done;

	len = sprintf(buf,
		"gvt: vgpu %d turns on non-privileged batch buffers scanning on Engines:",
		vgpu->id);

	s = buf + len;

	for (id = 0; id < I915_NUM_ENGINES; id++) {
		struct intel_engine_cs *engine;

		engine = dev_priv->engine[id];
		if (engine && (val & (1 << id))) {
			len = snprintf(s, 4, "%d, ", engine->id);
			s += len;
		} else
			val &=  ~(1 << id);
	}

	if (val)
		sprintf(s, "low performance expected.");

	pr_warn("%s\n", buf);

done:
	vgpu->scan_nonprivbb = val;
	return 0;
}