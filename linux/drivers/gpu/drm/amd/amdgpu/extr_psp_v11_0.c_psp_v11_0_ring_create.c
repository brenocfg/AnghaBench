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
struct psp_ring {unsigned int ring_size; int /*<<< orphan*/  ring_mem_mc_addr; } ;
struct psp_context {struct amdgpu_device* adev; struct psp_ring km_ring; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum psp_ring_type { ____Placeholder_psp_ring_type } psp_ring_type ;

/* Variables and functions */
 unsigned int GFX_CTRL_CMD_ID_INIT_GPCOM_RING ; 
 int /*<<< orphan*/  MP0 ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmMP0_SMN_C2PMSG_101 ; 
 int /*<<< orphan*/  mmMP0_SMN_C2PMSG_102 ; 
 int /*<<< orphan*/  mmMP0_SMN_C2PMSG_103 ; 
 int /*<<< orphan*/  mmMP0_SMN_C2PMSG_64 ; 
 int /*<<< orphan*/  mmMP0_SMN_C2PMSG_69 ; 
 int /*<<< orphan*/  mmMP0_SMN_C2PMSG_70 ; 
 int /*<<< orphan*/  mmMP0_SMN_C2PMSG_71 ; 
 scalar_t__ psp_v11_0_support_vmr_ring (struct psp_context*) ; 
 int psp_wait_for (struct psp_context*,int /*<<< orphan*/ ,int,int,int) ; 
 unsigned int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int psp_v11_0_ring_create(struct psp_context *psp,
				enum psp_ring_type ring_type)
{
	int ret = 0;
	unsigned int psp_ring_reg = 0;
	struct psp_ring *ring = &psp->km_ring;
	struct amdgpu_device *adev = psp->adev;

	if (psp_v11_0_support_vmr_ring(psp)) {
		/* Write low address of the ring to C2PMSG_102 */
		psp_ring_reg = lower_32_bits(ring->ring_mem_mc_addr);
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_102, psp_ring_reg);
		/* Write high address of the ring to C2PMSG_103 */
		psp_ring_reg = upper_32_bits(ring->ring_mem_mc_addr);
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_103, psp_ring_reg);

		/* Write the ring initialization command to C2PMSG_101 */
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_101,
					     GFX_CTRL_CMD_ID_INIT_GPCOM_RING);

		/* there might be handshake issue with hardware which needs delay */
		mdelay(20);

		/* Wait for response flag (bit 31) in C2PMSG_101 */
		ret = psp_wait_for(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_101),
				   0x80000000, 0x8000FFFF, false);

	} else {
		/* Write low address of the ring to C2PMSG_69 */
		psp_ring_reg = lower_32_bits(ring->ring_mem_mc_addr);
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_69, psp_ring_reg);
		/* Write high address of the ring to C2PMSG_70 */
		psp_ring_reg = upper_32_bits(ring->ring_mem_mc_addr);
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_70, psp_ring_reg);
		/* Write size of ring to C2PMSG_71 */
		psp_ring_reg = ring->ring_size;
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_71, psp_ring_reg);
		/* Write the ring initialization command to C2PMSG_64 */
		psp_ring_reg = ring_type;
		psp_ring_reg = psp_ring_reg << 16;
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_64, psp_ring_reg);

		/* there might be handshake issue with hardware which needs delay */
		mdelay(20);

		/* Wait for response flag (bit 31) in C2PMSG_64 */
		ret = psp_wait_for(psp, SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
				   0x80000000, 0x8000FFFF, false);
	}

	return ret;
}