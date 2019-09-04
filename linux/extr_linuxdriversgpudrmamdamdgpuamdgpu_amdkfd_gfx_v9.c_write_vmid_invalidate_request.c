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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct kgd_dev {int dummy; } ;
struct amdgpu_device {int /*<<< orphan*/  srbm_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  GC ; 
 int /*<<< orphan*/  MMHUB ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VM_INVALIDATE_ENG16_REQ__FLUSH_TYPE__SHIFT ; 
 int VM_INVALIDATE_ENG16_REQ__INVALIDATE_L1_PTES_MASK ; 
 int VM_INVALIDATE_ENG16_REQ__INVALIDATE_L2_PDE0_MASK ; 
 int VM_INVALIDATE_ENG16_REQ__INVALIDATE_L2_PDE1_MASK ; 
 int VM_INVALIDATE_ENG16_REQ__INVALIDATE_L2_PDE2_MASK ; 
 int VM_INVALIDATE_ENG16_REQ__INVALIDATE_L2_PTES_MASK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  mmMMHUB_VM_INVALIDATE_ENG16_ACK ; 
 int /*<<< orphan*/  mmMMHUB_VM_INVALIDATE_ENG16_ADDR_RANGE_HI32 ; 
 int /*<<< orphan*/  mmMMHUB_VM_INVALIDATE_ENG16_ADDR_RANGE_LO32 ; 
 int /*<<< orphan*/  mmMMHUB_VM_INVALIDATE_ENG16_REQ ; 
 int /*<<< orphan*/  mmVM_INVALIDATE_ENG16_ACK ; 
 int /*<<< orphan*/  mmVM_INVALIDATE_ENG16_ADDR_RANGE_HI32 ; 
 int /*<<< orphan*/  mmVM_INVALIDATE_ENG16_ADDR_RANGE_LO32 ; 
 int /*<<< orphan*/  mmVM_INVALIDATE_ENG16_REQ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_vmid_invalidate_request(struct kgd_dev *kgd, uint8_t vmid)
{
	struct amdgpu_device *adev = (struct amdgpu_device *) kgd;
	uint32_t req = (1 << vmid) |
		(0 << VM_INVALIDATE_ENG16_REQ__FLUSH_TYPE__SHIFT) | /* legacy */
		VM_INVALIDATE_ENG16_REQ__INVALIDATE_L2_PTES_MASK |
		VM_INVALIDATE_ENG16_REQ__INVALIDATE_L2_PDE0_MASK |
		VM_INVALIDATE_ENG16_REQ__INVALIDATE_L2_PDE1_MASK |
		VM_INVALIDATE_ENG16_REQ__INVALIDATE_L2_PDE2_MASK |
		VM_INVALIDATE_ENG16_REQ__INVALIDATE_L1_PTES_MASK;

	mutex_lock(&adev->srbm_mutex);

	/* Use legacy mode tlb invalidation.
	 *
	 * Currently on Raven the code below is broken for anything but
	 * legacy mode due to a MMHUB power gating problem. A workaround
	 * is for MMHUB to wait until the condition PER_VMID_INVALIDATE_REQ
	 * == PER_VMID_INVALIDATE_ACK instead of simply waiting for the ack
	 * bit.
	 *
	 * TODO 1: agree on the right set of invalidation registers for
	 * KFD use. Use the last one for now. Invalidate both GC and
	 * MMHUB.
	 *
	 * TODO 2: support range-based invalidation, requires kfg2kgd
	 * interface change
	 */
	WREG32(SOC15_REG_OFFSET(GC, 0, mmVM_INVALIDATE_ENG16_ADDR_RANGE_LO32),
				0xffffffff);
	WREG32(SOC15_REG_OFFSET(GC, 0, mmVM_INVALIDATE_ENG16_ADDR_RANGE_HI32),
				0x0000001f);

	WREG32(SOC15_REG_OFFSET(MMHUB, 0,
				mmMMHUB_VM_INVALIDATE_ENG16_ADDR_RANGE_LO32),
				0xffffffff);
	WREG32(SOC15_REG_OFFSET(MMHUB, 0,
				mmMMHUB_VM_INVALIDATE_ENG16_ADDR_RANGE_HI32),
				0x0000001f);

	WREG32(SOC15_REG_OFFSET(GC, 0, mmVM_INVALIDATE_ENG16_REQ), req);

	WREG32(SOC15_REG_OFFSET(MMHUB, 0, mmMMHUB_VM_INVALIDATE_ENG16_REQ),
				req);

	while (!(RREG32(SOC15_REG_OFFSET(GC, 0, mmVM_INVALIDATE_ENG16_ACK)) &
					(1 << vmid)))
		cpu_relax();

	while (!(RREG32(SOC15_REG_OFFSET(MMHUB, 0,
					mmMMHUB_VM_INVALIDATE_ENG16_ACK)) &
					(1 << vmid)))
		cpu_relax();

	mutex_unlock(&adev->srbm_mutex);

}