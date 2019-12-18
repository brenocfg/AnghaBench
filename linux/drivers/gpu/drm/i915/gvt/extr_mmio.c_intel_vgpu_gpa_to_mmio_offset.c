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
typedef  int u64 ;
struct intel_vgpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_BASE_ADDRESS_0 ; 
 int intel_vgpu_get_bar_gpa (struct intel_vgpu*,int /*<<< orphan*/ ) ; 

int intel_vgpu_gpa_to_mmio_offset(struct intel_vgpu *vgpu, u64 gpa)
{
	u64 gttmmio_gpa = intel_vgpu_get_bar_gpa(vgpu, PCI_BASE_ADDRESS_0);
	return gpa - gttmmio_gpa;
}