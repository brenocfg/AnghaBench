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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  ucode_array_offset_bytes; int /*<<< orphan*/  ucode_size_bytes; } ;
struct smc_firmware_header_v1_0 {TYPE_2__ header; int /*<<< orphan*/  ucode_start_addr; } ;
struct radeon_device {int family; int /*<<< orphan*/  smc_idx_lock; TYPE_1__* smc_fw; scalar_t__ new_fw; } ;
struct TYPE_3__ {int data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_INCREMENT_IND_0 ; 
 int BONAIRE_SMC_UCODE_SIZE ; 
 int BONAIRE_SMC_UCODE_START ; 
 int /*<<< orphan*/  BUG () ; 
#define  CHIP_BONAIRE 129 
#define  CHIP_HAWAII 128 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int HAWAII_SMC_UCODE_SIZE ; 
 int HAWAII_SMC_UCODE_START ; 
 int /*<<< orphan*/  SMC_IND_ACCESS_CNTL ; 
 int /*<<< orphan*/  SMC_IND_DATA_0 ; 
 int /*<<< orphan*/  SMC_IND_INDEX_0 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ucode_print_smc_hdr (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ci_load_smc_ucode(struct radeon_device *rdev, u32 limit)
{
	unsigned long flags;
	u32 ucode_start_address;
	u32 ucode_size;
	const u8 *src;
	u32 data;

	if (!rdev->smc_fw)
		return -EINVAL;

	if (rdev->new_fw) {
		const struct smc_firmware_header_v1_0 *hdr =
			(const struct smc_firmware_header_v1_0 *)rdev->smc_fw->data;

		radeon_ucode_print_smc_hdr(&hdr->header);

		ucode_start_address = le32_to_cpu(hdr->ucode_start_addr);
		ucode_size = le32_to_cpu(hdr->header.ucode_size_bytes);
		src = (const u8 *)
			(rdev->smc_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
	} else {
		switch (rdev->family) {
		case CHIP_BONAIRE:
			ucode_start_address = BONAIRE_SMC_UCODE_START;
			ucode_size = BONAIRE_SMC_UCODE_SIZE;
			break;
		case CHIP_HAWAII:
			ucode_start_address = HAWAII_SMC_UCODE_START;
			ucode_size = HAWAII_SMC_UCODE_SIZE;
			break;
		default:
			DRM_ERROR("unknown asic in smc ucode loader\n");
			BUG();
		}

		src = (const u8 *)rdev->smc_fw->data;
	}

	if (ucode_size & 3)
		return -EINVAL;

	spin_lock_irqsave(&rdev->smc_idx_lock, flags);
	WREG32(SMC_IND_INDEX_0, ucode_start_address);
	WREG32_P(SMC_IND_ACCESS_CNTL, AUTO_INCREMENT_IND_0, ~AUTO_INCREMENT_IND_0);
	while (ucode_size >= 4) {
		/* SMC address space is BE */
		data = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];

		WREG32(SMC_IND_DATA_0, data);

		src += 4;
		ucode_size -= 4;
	}
	WREG32_P(SMC_IND_ACCESS_CNTL, 0, ~AUTO_INCREMENT_IND_0);
	spin_unlock_irqrestore(&rdev->smc_idx_lock, flags);

	return 0;
}