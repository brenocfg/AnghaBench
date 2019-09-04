#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct intel_vgpu {int /*<<< orphan*/  id; TYPE_2__* gvt; } ;
struct drm_i915_private {TYPE_1__** engine; } ;
struct TYPE_4__ {struct drm_i915_private* dev_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmio_base; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RING_NOPID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_err (char*,int /*<<< orphan*/ ,int,unsigned int,...) ; 
 int /*<<< orphan*/  i915_mmio_reg_offset (int /*<<< orphan*/ ) ; 
 scalar_t__ in_whitelist (int /*<<< orphan*/ ) ; 
 int intel_gvt_render_mmio_to_ring_id (TYPE_2__*,unsigned int) ; 
 int intel_vgpu_default_mmio_write (struct intel_vgpu*,unsigned int,void*,unsigned int) ; 

__attribute__((used)) static int force_nonpriv_write(struct intel_vgpu *vgpu,
	unsigned int offset, void *p_data, unsigned int bytes)
{
	u32 reg_nonpriv = *(u32 *)p_data;
	int ring_id = intel_gvt_render_mmio_to_ring_id(vgpu->gvt, offset);
	u32 ring_base;
	struct drm_i915_private *dev_priv = vgpu->gvt->dev_priv;
	int ret = -EINVAL;

	if ((bytes != 4) || ((offset & (bytes - 1)) != 0) || ring_id < 0) {
		gvt_err("vgpu(%d) ring %d Invalid FORCE_NONPRIV offset %x(%dB)\n",
			vgpu->id, ring_id, offset, bytes);
		return ret;
	}

	ring_base = dev_priv->engine[ring_id]->mmio_base;

	if (in_whitelist(reg_nonpriv) ||
		reg_nonpriv == i915_mmio_reg_offset(RING_NOPID(ring_base))) {
		ret = intel_vgpu_default_mmio_write(vgpu, offset, p_data,
			bytes);
	} else
		gvt_err("vgpu(%d) Invalid FORCE_NONPRIV write %x at offset %x\n",
			vgpu->id, reg_nonpriv, offset);

	return 0;
}