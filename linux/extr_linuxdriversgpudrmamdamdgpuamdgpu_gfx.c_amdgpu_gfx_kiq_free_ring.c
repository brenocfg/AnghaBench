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
struct amdgpu_ring {TYPE_2__* adev; } ;
struct amdgpu_irq_src {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg_val_offs; } ;
struct TYPE_4__ {TYPE_1__ virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_device_wb_free (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ring_fini (struct amdgpu_ring*) ; 

void amdgpu_gfx_kiq_free_ring(struct amdgpu_ring *ring,
			      struct amdgpu_irq_src *irq)
{
	amdgpu_device_wb_free(ring->adev, ring->adev->virt.reg_val_offs);
	amdgpu_ring_fini(ring);
}