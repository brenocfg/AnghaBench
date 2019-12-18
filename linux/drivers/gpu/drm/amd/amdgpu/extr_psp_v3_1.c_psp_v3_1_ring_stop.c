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
struct psp_context {struct amdgpu_device* adev; } ;
struct amdgpu_device {int dummy; } ;
typedef  enum psp_ring_type { ____Placeholder_psp_ring_type } psp_ring_type ;

/* Variables and functions */
 unsigned int GFX_CTRL_CMD_ID_DESTROY_GPCOM_RING ; 
 int /*<<< orphan*/  MP0 ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmMP0_SMN_C2PMSG_101 ; 
 int /*<<< orphan*/  mmMP0_SMN_C2PMSG_64 ; 
 scalar_t__ psp_v3_1_support_vmr_ring (struct psp_context*) ; 
 int psp_wait_for (struct psp_context*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int psp_v3_1_ring_stop(struct psp_context *psp,
			      enum psp_ring_type ring_type)
{
	int ret = 0;
	unsigned int psp_ring_reg = 0;
	struct amdgpu_device *adev = psp->adev;

	if (psp_v3_1_support_vmr_ring(psp)) {
		/* Write the Destroy GPCOM ring command to C2PMSG_101 */
		psp_ring_reg = GFX_CTRL_CMD_ID_DESTROY_GPCOM_RING;
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_101, psp_ring_reg);

		/* there might be handshake issue which needs delay */
		mdelay(20);

		/* Wait for response flag (bit 31) in C2PMSG_101 */
		ret = psp_wait_for(psp,
				SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_101),
				0x80000000, 0x80000000, false);
	} else {
		/* Write the ring destroy command to C2PMSG_64 */
		psp_ring_reg = 3 << 16;
		WREG32_SOC15(MP0, 0, mmMP0_SMN_C2PMSG_64, psp_ring_reg);

		/* there might be handshake issue which needs delay */
		mdelay(20);

		/* Wait for response flag (bit 31) in C2PMSG_64 */
		ret = psp_wait_for(psp,
				SOC15_REG_OFFSET(MP0, 0, mmMP0_SMN_C2PMSG_64),
				0x80000000, 0x80000000, false);
	}

	return ret;
}