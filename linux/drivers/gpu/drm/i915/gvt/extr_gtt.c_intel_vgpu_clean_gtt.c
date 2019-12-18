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
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_vgpu_destroy_all_ppgtt_mm (struct intel_vgpu*) ; 
 int /*<<< orphan*/  intel_vgpu_destroy_ggtt_mm (struct intel_vgpu*) ; 
 int /*<<< orphan*/  release_scratch_page_tree (struct intel_vgpu*) ; 

void intel_vgpu_clean_gtt(struct intel_vgpu *vgpu)
{
	intel_vgpu_destroy_all_ppgtt_mm(vgpu);
	intel_vgpu_destroy_ggtt_mm(vgpu);
	release_scratch_page_tree(vgpu);
}