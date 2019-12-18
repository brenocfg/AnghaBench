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
typedef  int u32 ;
struct radeon_device {int family; int usec_timeout; scalar_t__ new_fw; TYPE_1__* mc_fw; } ;
struct TYPE_4__ {int /*<<< orphan*/  ucode_array_offset_bytes; int /*<<< orphan*/  ucode_size_bytes; } ;
struct mc_firmware_header_v1_0 {TYPE_2__ header; int /*<<< orphan*/  io_debug_array_offset_bytes; int /*<<< orphan*/  io_debug_size_bytes; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int size; scalar_t__ data; } ;

/* Variables and functions */
#define  CHIP_HAINAN 132 
#define  CHIP_OLAND 131 
#define  CHIP_PITCAIRN 130 
#define  CHIP_TAHITI 129 
#define  CHIP_VERDE 128 
 int EINVAL ; 
 int /*<<< orphan*/  MC_SEQ_IO_DEBUG_DATA ; 
 int /*<<< orphan*/  MC_SEQ_IO_DEBUG_INDEX ; 
 int /*<<< orphan*/  MC_SEQ_SUP_CNTL ; 
 int /*<<< orphan*/  MC_SEQ_SUP_PGM ; 
 int /*<<< orphan*/  MC_SEQ_TRAIN_WAKEUP_CNTL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int RUN_MASK ; 
 int TAHITI_IO_MC_REGS_SIZE ; 
 int TRAIN_DONE_D0 ; 
 int TRAIN_DONE_D1 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hainan_io_mc_regs ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oland_io_mc_regs ; 
 int /*<<< orphan*/  pitcairn_io_mc_regs ; 
 int /*<<< orphan*/  radeon_ucode_print_mc_hdr (TYPE_2__*) ; 
 int /*<<< orphan*/  tahiti_io_mc_regs ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  verde_io_mc_regs ; 

int si_mc_load_microcode(struct radeon_device *rdev)
{
	const __be32 *fw_data = NULL;
	const __le32 *new_fw_data = NULL;
	u32 running;
	u32 *io_mc_regs = NULL;
	const __le32 *new_io_mc_regs = NULL;
	int i, regs_size, ucode_size;

	if (!rdev->mc_fw)
		return -EINVAL;

	if (rdev->new_fw) {
		const struct mc_firmware_header_v1_0 *hdr =
			(const struct mc_firmware_header_v1_0 *)rdev->mc_fw->data;

		radeon_ucode_print_mc_hdr(&hdr->header);
		regs_size = le32_to_cpu(hdr->io_debug_size_bytes) / (4 * 2);
		new_io_mc_regs = (const __le32 *)
			(rdev->mc_fw->data + le32_to_cpu(hdr->io_debug_array_offset_bytes));
		ucode_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
		new_fw_data = (const __le32 *)
			(rdev->mc_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
	} else {
		ucode_size = rdev->mc_fw->size / 4;

		switch (rdev->family) {
		case CHIP_TAHITI:
			io_mc_regs = (u32 *)&tahiti_io_mc_regs;
			regs_size = TAHITI_IO_MC_REGS_SIZE;
			break;
		case CHIP_PITCAIRN:
			io_mc_regs = (u32 *)&pitcairn_io_mc_regs;
			regs_size = TAHITI_IO_MC_REGS_SIZE;
			break;
		case CHIP_VERDE:
		default:
			io_mc_regs = (u32 *)&verde_io_mc_regs;
			regs_size = TAHITI_IO_MC_REGS_SIZE;
			break;
		case CHIP_OLAND:
			io_mc_regs = (u32 *)&oland_io_mc_regs;
			regs_size = TAHITI_IO_MC_REGS_SIZE;
			break;
		case CHIP_HAINAN:
			io_mc_regs = (u32 *)&hainan_io_mc_regs;
			regs_size = TAHITI_IO_MC_REGS_SIZE;
			break;
		}
		fw_data = (const __be32 *)rdev->mc_fw->data;
	}

	running = RREG32(MC_SEQ_SUP_CNTL) & RUN_MASK;

	if (running == 0) {
		/* reset the engine and set to writable */
		WREG32(MC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000010);

		/* load mc io regs */
		for (i = 0; i < regs_size; i++) {
			if (rdev->new_fw) {
				WREG32(MC_SEQ_IO_DEBUG_INDEX, le32_to_cpup(new_io_mc_regs++));
				WREG32(MC_SEQ_IO_DEBUG_DATA, le32_to_cpup(new_io_mc_regs++));
			} else {
				WREG32(MC_SEQ_IO_DEBUG_INDEX, io_mc_regs[(i << 1)]);
				WREG32(MC_SEQ_IO_DEBUG_DATA, io_mc_regs[(i << 1) + 1]);
			}
		}
		/* load the MC ucode */
		for (i = 0; i < ucode_size; i++) {
			if (rdev->new_fw)
				WREG32(MC_SEQ_SUP_PGM, le32_to_cpup(new_fw_data++));
			else
				WREG32(MC_SEQ_SUP_PGM, be32_to_cpup(fw_data++));
		}

		/* put the engine back into the active state */
		WREG32(MC_SEQ_SUP_CNTL, 0x00000008);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000004);
		WREG32(MC_SEQ_SUP_CNTL, 0x00000001);

		/* wait for training to complete */
		for (i = 0; i < rdev->usec_timeout; i++) {
			if (RREG32(MC_SEQ_TRAIN_WAKEUP_CNTL) & TRAIN_DONE_D0)
				break;
			udelay(1);
		}
		for (i = 0; i < rdev->usec_timeout; i++) {
			if (RREG32(MC_SEQ_TRAIN_WAKEUP_CNTL) & TRAIN_DONE_D1)
				break;
			udelay(1);
		}
	}

	return 0;
}