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
typedef  scalar_t__ u32 ;
struct mmio_diff_param {int /*<<< orphan*/  total; int /*<<< orphan*/  diff; int /*<<< orphan*/  diff_mmio_list; int /*<<< orphan*/  vgpu; } ;
struct intel_gvt {struct drm_i915_private* dev_priv; } ;
struct drm_i915_private {int /*<<< orphan*/  uncore; } ;
struct diff_mmio {int /*<<< orphan*/  node; scalar_t__ vreg; scalar_t__ preg; scalar_t__ offset; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _MMIO (scalar_t__) ; 
 scalar_t__ intel_uncore_read_notrace (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct diff_mmio* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vgpu_vreg (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline int mmio_diff_handler(struct intel_gvt *gvt,
				    u32 offset, void *data)
{
	struct drm_i915_private *i915 = gvt->dev_priv;
	struct mmio_diff_param *param = data;
	struct diff_mmio *node;
	u32 preg, vreg;

	preg = intel_uncore_read_notrace(&i915->uncore, _MMIO(offset));
	vreg = vgpu_vreg(param->vgpu, offset);

	if (preg != vreg) {
		node = kmalloc(sizeof(*node), GFP_KERNEL);
		if (!node)
			return -ENOMEM;

		node->offset = offset;
		node->preg = preg;
		node->vreg = vreg;
		list_add(&node->node, &param->diff_mmio_list);
		param->diff++;
	}
	param->total++;
	return 0;
}