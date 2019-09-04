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
struct vfio_region {int dummy; } ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void intel_vgpu_reg_release_opregion(struct intel_vgpu *vgpu,
		struct vfio_region *region)
{
}