#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int /*<<< orphan*/  ucode_array_offset_bytes; int /*<<< orphan*/  ucode_size_bytes; int /*<<< orphan*/  ucode_version; } ;
struct mc_firmware_header_v1_0 {TYPE_3__ header; int /*<<< orphan*/  io_debug_array_offset_bytes; int /*<<< orphan*/  io_debug_size_bytes; } ;
struct TYPE_5__ {int fw_version; TYPE_1__* fw; } ;
struct amdgpu_device {int usec_timeout; TYPE_2__ gmc; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MC_SEQ_SUP_CNTL ; 
 int /*<<< orphan*/  MC_SEQ_TRAIN_WAKEUP_CNTL ; 
 scalar_t__ REG_GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUN ; 
 int /*<<< orphan*/  TRAIN_DONE_D0 ; 
 int /*<<< orphan*/  TRAIN_DONE_D1 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ amdgpu_sriov_bios (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ucode_print_mc_hdr (TYPE_3__*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmMC_SEQ_IO_DEBUG_DATA ; 
 int /*<<< orphan*/  mmMC_SEQ_IO_DEBUG_INDEX ; 
 int /*<<< orphan*/  mmMC_SEQ_SUP_CNTL ; 
 int /*<<< orphan*/  mmMC_SEQ_SUP_PGM ; 
 int /*<<< orphan*/  mmMC_SEQ_TRAIN_WAKEUP_CNTL ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int gmc_v8_0_tonga_mc_load_microcode(struct amdgpu_device *adev)
{
	const struct mc_firmware_header_v1_0 *hdr;
	const __le32 *fw_data = NULL;
	const __le32 *io_mc_regs = NULL;
	u32 running;
	int i, ucode_size, regs_size;

	/* Skip MC ucode loading on SR-IOV capable boards.
	 * vbios does this for us in asic_init in that case.
	 * Skip MC ucode loading on VF, because hypervisor will do that
	 * for this adaptor.
	 */
	if (amdgpu_sriov_bios(adev))
		return 0;

	if (!adev->gmc.fw)
		return -EINVAL;

	hdr = (const struct mc_firmware_header_v1_0 *)adev->gmc.fw->data;
	amdgpu_ucode_print_mc_hdr(&hdr->header);

	adev->gmc.fw_version = le32_to_cpu(hdr->header.ucode_version);
	regs_size = le32_to_cpu(hdr->io_debug_size_bytes) / (4 * 2);
	io_mc_regs = (const __le32 *)
		(adev->gmc.fw->data + le32_to_cpu(hdr->io_debug_array_offset_bytes));
	ucode_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
	fw_data = (const __le32 *)
		(adev->gmc.fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));

	running = REG_GET_FIELD(RREG32(mmMC_SEQ_SUP_CNTL), MC_SEQ_SUP_CNTL, RUN);

	if (running == 0) {
		/* reset the engine and set to writable */
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000010);

		/* load mc io regs */
		for (i = 0; i < regs_size; i++) {
			WREG32(mmMC_SEQ_IO_DEBUG_INDEX, le32_to_cpup(io_mc_regs++));
			WREG32(mmMC_SEQ_IO_DEBUG_DATA, le32_to_cpup(io_mc_regs++));
		}
		/* load the MC ucode */
		for (i = 0; i < ucode_size; i++)
			WREG32(mmMC_SEQ_SUP_PGM, le32_to_cpup(fw_data++));

		/* put the engine back into the active state */
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000004);
		WREG32(mmMC_SEQ_SUP_CNTL, 0x00000001);

		/* wait for training to complete */
		for (i = 0; i < adev->usec_timeout; i++) {
			if (REG_GET_FIELD(RREG32(mmMC_SEQ_TRAIN_WAKEUP_CNTL),
					  MC_SEQ_TRAIN_WAKEUP_CNTL, TRAIN_DONE_D0))
				break;
			udelay(1);
		}
		for (i = 0; i < adev->usec_timeout; i++) {
			if (REG_GET_FIELD(RREG32(mmMC_SEQ_TRAIN_WAKEUP_CNTL),
					  MC_SEQ_TRAIN_WAKEUP_CNTL, TRAIN_DONE_D1))
				break;
			udelay(1);
		}
	}

	return 0;
}