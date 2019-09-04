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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_4__ {TYPE_1__* bar; } ;
struct intel_vgpu {TYPE_2__ cfg_space; } ;
typedef  int phys_addr_t ;
struct TYPE_3__ {int tracked; } ;

/* Variables and functions */
 size_t INTEL_GVT_PCI_BAR_APERTURE ; 
 int PAGE_SHIFT ; 
 size_t PCI_BASE_ADDRESS_2 ; 
 int PCI_BASE_ADDRESS_MEM_TYPE_64 ; 
 int intel_gvt_hypervisor_map_gfn_to_mfn (struct intel_vgpu*,int,int,unsigned long,int) ; 
 int vgpu_aperture_offset (struct intel_vgpu*) ; 
 int vgpu_aperture_pa_base (struct intel_vgpu*) ; 
 unsigned long vgpu_aperture_sz (struct intel_vgpu*) ; 
 int* vgpu_cfg_space (struct intel_vgpu*) ; 

__attribute__((used)) static int map_aperture(struct intel_vgpu *vgpu, bool map)
{
	phys_addr_t aperture_pa = vgpu_aperture_pa_base(vgpu);
	unsigned long aperture_sz = vgpu_aperture_sz(vgpu);
	u64 first_gfn;
	u64 val;
	int ret;

	if (map == vgpu->cfg_space.bar[INTEL_GVT_PCI_BAR_APERTURE].tracked)
		return 0;

	val = vgpu_cfg_space(vgpu)[PCI_BASE_ADDRESS_2];
	if (val & PCI_BASE_ADDRESS_MEM_TYPE_64)
		val = *(u64 *)(vgpu_cfg_space(vgpu) + PCI_BASE_ADDRESS_2);
	else
		val = *(u32 *)(vgpu_cfg_space(vgpu) + PCI_BASE_ADDRESS_2);

	first_gfn = (val + vgpu_aperture_offset(vgpu)) >> PAGE_SHIFT;

	ret = intel_gvt_hypervisor_map_gfn_to_mfn(vgpu, first_gfn,
						  aperture_pa >> PAGE_SHIFT,
						  aperture_sz >> PAGE_SHIFT,
						  map);
	if (ret)
		return ret;

	vgpu->cfg_space.bar[INTEL_GVT_PCI_BAR_APERTURE].tracked = map;
	return 0;
}