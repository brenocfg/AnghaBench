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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_ring {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_VMID ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  MODE ; 
 int /*<<< orphan*/  REG_SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SQ_CMD ; 
 int /*<<< orphan*/  VM_ID ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmSQ_CMD ; 

__attribute__((used)) static void gfx_v8_0_ring_soft_recovery(struct amdgpu_ring *ring, unsigned vmid)
{
	struct amdgpu_device *adev = ring->adev;
	uint32_t value = 0;

	value = REG_SET_FIELD(value, SQ_CMD, CMD, 0x03);
	value = REG_SET_FIELD(value, SQ_CMD, MODE, 0x01);
	value = REG_SET_FIELD(value, SQ_CMD, CHECK_VMID, 1);
	value = REG_SET_FIELD(value, SQ_CMD, VM_ID, vmid);
	WREG32(mmSQ_CMD, value);
}