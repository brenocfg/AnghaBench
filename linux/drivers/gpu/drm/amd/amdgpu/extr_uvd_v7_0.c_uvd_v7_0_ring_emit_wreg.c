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
typedef  int uint32_t ;
struct amdgpu_ring {int /*<<< orphan*/  me; struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int PACKET0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int /*<<< orphan*/  amdgpu_ring_write (struct amdgpu_ring*,int) ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_CMD ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_DATA0 ; 
 int /*<<< orphan*/  mmUVD_GPCOM_VCPU_DATA1 ; 

__attribute__((used)) static void uvd_v7_0_ring_emit_wreg(struct amdgpu_ring *ring,
				    uint32_t reg, uint32_t val)
{
	struct amdgpu_device *adev = ring->adev;

	amdgpu_ring_write(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_ring_write(ring, reg << 2);
	amdgpu_ring_write(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_ring_write(ring, val);
	amdgpu_ring_write(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_ring_write(ring, 8);
}