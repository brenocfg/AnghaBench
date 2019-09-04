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
struct amdgpu_ring {int* ring; struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 void* PACKETJ (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PACKETJ_TYPE0 ; 
 int SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UVD ; 
 int /*<<< orphan*/  mmUVD_JRBC_EXTERNAL_REG_BASE ; 

__attribute__((used)) static void vcn_v1_0_jpeg_ring_patch_wreg(struct amdgpu_ring *ring, uint32_t *ptr, uint32_t reg_offset, uint32_t val)
{
	struct amdgpu_device *adev = ring->adev;
	ring->ring[(*ptr)++] = PACKETJ(SOC15_REG_OFFSET(UVD, 0, mmUVD_JRBC_EXTERNAL_REG_BASE), 0, 0, PACKETJ_TYPE0);
	if (((reg_offset >= 0x1f800) && (reg_offset <= 0x21fff)) ||
		((reg_offset >= 0x1e000) && (reg_offset <= 0x1e1ff))) {
		ring->ring[(*ptr)++] = 0;
		ring->ring[(*ptr)++] = PACKETJ((reg_offset >> 2), 0, 0, PACKETJ_TYPE0);
	} else {
		ring->ring[(*ptr)++] = reg_offset;
		ring->ring[(*ptr)++] = PACKETJ(0, 0, 0, PACKETJ_TYPE0);
	}
	ring->ring[(*ptr)++] = val;
}