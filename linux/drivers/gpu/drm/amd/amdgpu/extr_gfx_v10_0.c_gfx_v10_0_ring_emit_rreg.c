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
typedef  int uint32_t ;
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct TYPE_4__ {int reg_val_offs; } ;
struct TYPE_3__ {scalar_t__ gpu_addr; } ;
struct amdgpu_device {TYPE_2__ virt; TYPE_1__ wb; } ;

/* Variables and functions */
 int PACKET3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PACKET3_COPY_DATA ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int lower_32_bits (scalar_t__) ; 
 int upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void gfx_v10_0_ring_emit_rreg(struct amdgpu_ring *ring, uint32_t reg)
{
	struct amdgpu_device *adev = ring->adev;

	amdgpu_ring_write(ring, PACKET3(PACKET3_COPY_DATA, 4));
	amdgpu_ring_write(ring, 0 |	/* src: register*/
				(5 << 8) |	/* dst: memory */
				(1 << 20));	/* write confirm */
	amdgpu_ring_write(ring, reg);
	amdgpu_ring_write(ring, 0);
	amdgpu_ring_write(ring, lower_32_bits(adev->wb.gpu_addr +
				adev->virt.reg_val_offs * 4));
	amdgpu_ring_write(ring, upper_32_bits(adev->wb.gpu_addr +
				adev->virt.reg_val_offs * 4));
}