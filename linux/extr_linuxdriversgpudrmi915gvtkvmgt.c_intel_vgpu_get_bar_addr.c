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
typedef  int uint64_t ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ virtual_cfg_space; } ;
struct intel_vgpu {TYPE_1__ cfg_space; } ;

/* Variables and functions */
 int PCI_BASE_ADDRESS_MEM_MASK ; 
#define  PCI_BASE_ADDRESS_MEM_TYPE_1M 130 
#define  PCI_BASE_ADDRESS_MEM_TYPE_32 129 
#define  PCI_BASE_ADDRESS_MEM_TYPE_64 128 
 int PCI_BASE_ADDRESS_MEM_TYPE_MASK ; 

__attribute__((used)) static uint64_t intel_vgpu_get_bar_addr(struct intel_vgpu *vgpu, int bar)
{
	u32 start_lo, start_hi;
	u32 mem_type;

	start_lo = (*(u32 *)(vgpu->cfg_space.virtual_cfg_space + bar)) &
			PCI_BASE_ADDRESS_MEM_MASK;
	mem_type = (*(u32 *)(vgpu->cfg_space.virtual_cfg_space + bar)) &
			PCI_BASE_ADDRESS_MEM_TYPE_MASK;

	switch (mem_type) {
	case PCI_BASE_ADDRESS_MEM_TYPE_64:
		start_hi = (*(u32 *)(vgpu->cfg_space.virtual_cfg_space
						+ bar + 4));
		break;
	case PCI_BASE_ADDRESS_MEM_TYPE_32:
	case PCI_BASE_ADDRESS_MEM_TYPE_1M:
		/* 1M mem BAR treated as 32-bit BAR */
	default:
		/* mem unknown type treated as 32-bit BAR */
		start_hi = 0;
		break;
	}

	return ((u64)start_hi << 32) | start_lo;
}