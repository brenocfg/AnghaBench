#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_6__ {struct drm_i915_private* i915; } ;
struct i915_ppgtt {int /*<<< orphan*/  pd; TYPE_3__ vm; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct drm_i915_private {TYPE_1__ vgpu; } ;
typedef  enum vgt_g2v_type { ____Placeholder_vgt_g2v_type } vgt_g2v_type ;
struct TYPE_5__ {int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; } ;

/* Variables and functions */
 int GEN8_3LVL_PDPES ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int VGT_G2V_PPGTT_L3_PAGE_TABLE_CREATE ; 
 int VGT_G2V_PPGTT_L3_PAGE_TABLE_DESTROY ; 
 int VGT_G2V_PPGTT_L4_PAGE_TABLE_CREATE ; 
 int VGT_G2V_PPGTT_L4_PAGE_TABLE_DESTROY ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g2v_notify ; 
 int /*<<< orphan*/  i915_page_dir_dma_addr (struct i915_ppgtt*,int) ; 
 scalar_t__ i915_vm_is_4lvl (TYPE_3__*) ; 
 int lower_32_bits (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* pdp ; 
 int /*<<< orphan*/  px_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  px_used (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  vgtif_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gen8_ppgtt_notify_vgt(struct i915_ppgtt *ppgtt, bool create)
{
	struct drm_i915_private *dev_priv = ppgtt->vm.i915;
	enum vgt_g2v_type msg;
	int i;

	if (create)
		atomic_inc(px_used(ppgtt->pd)); /* never remove */
	else
		atomic_dec(px_used(ppgtt->pd));

	mutex_lock(&dev_priv->vgpu.lock);

	if (i915_vm_is_4lvl(&ppgtt->vm)) {
		const u64 daddr = px_dma(ppgtt->pd);

		I915_WRITE(vgtif_reg(pdp[0].lo), lower_32_bits(daddr));
		I915_WRITE(vgtif_reg(pdp[0].hi), upper_32_bits(daddr));

		msg = (create ? VGT_G2V_PPGTT_L4_PAGE_TABLE_CREATE :
				VGT_G2V_PPGTT_L4_PAGE_TABLE_DESTROY);
	} else {
		for (i = 0; i < GEN8_3LVL_PDPES; i++) {
			const u64 daddr = i915_page_dir_dma_addr(ppgtt, i);

			I915_WRITE(vgtif_reg(pdp[i].lo), lower_32_bits(daddr));
			I915_WRITE(vgtif_reg(pdp[i].hi), upper_32_bits(daddr));
		}

		msg = (create ? VGT_G2V_PPGTT_L3_PAGE_TABLE_CREATE :
				VGT_G2V_PPGTT_L3_PAGE_TABLE_DESTROY);
	}

	/* g2v_notify atomically (via hv trap) consumes the message packet. */
	I915_WRITE(vgtif_reg(g2v_notify), msg);

	mutex_unlock(&dev_priv->vgpu.lock);
}