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
struct intel_vgpu {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {TYPE_1__* mpt; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dma_unmap_guest_page ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__ intel_gvt_host ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void intel_gvt_hypervisor_dma_unmap_guest_page(
		struct intel_vgpu *vgpu, dma_addr_t dma_addr)
{
	intel_gvt_host.mpt->dma_unmap_guest_page(vgpu->handle, dma_addr);
}