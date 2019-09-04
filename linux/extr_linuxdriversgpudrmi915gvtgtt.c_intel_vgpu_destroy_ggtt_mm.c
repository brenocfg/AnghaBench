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
struct TYPE_2__ {int /*<<< orphan*/ * ggtt_mm; } ;
struct intel_vgpu {TYPE_1__ gtt; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_vgpu_destroy_mm (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_vgpu_destroy_ggtt_mm(struct intel_vgpu *vgpu)
{
	intel_vgpu_destroy_mm(vgpu->gtt.ggtt_mm);
	vgpu->gtt.ggtt_mm = NULL;
}