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
struct intel_vgpu_ppgtt_spt {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  spt_tree; } ;
struct intel_vgpu {TYPE_1__ gtt; } ;

/* Variables and functions */
 struct intel_vgpu_ppgtt_spt* radix_tree_lookup (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline struct intel_vgpu_ppgtt_spt *intel_vgpu_find_spt_by_mfn(
		struct intel_vgpu *vgpu, unsigned long mfn)
{
	return radix_tree_lookup(&vgpu->gtt.spt_tree, mfn);
}