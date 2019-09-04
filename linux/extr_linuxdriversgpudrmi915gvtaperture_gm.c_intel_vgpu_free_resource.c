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
 int /*<<< orphan*/  free_resource (struct intel_vgpu*) ; 
 int /*<<< orphan*/  free_vgpu_fence (struct intel_vgpu*) ; 
 int /*<<< orphan*/  free_vgpu_gm (struct intel_vgpu*) ; 

void intel_vgpu_free_resource(struct intel_vgpu *vgpu)
{
	free_vgpu_gm(vgpu);
	free_vgpu_fence(vgpu);
	free_resource(vgpu);
}