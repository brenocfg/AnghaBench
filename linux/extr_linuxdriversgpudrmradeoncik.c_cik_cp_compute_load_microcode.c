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
typedef  int u32 ;
struct radeon_device {scalar_t__ family; TYPE_2__* mec_fw; TYPE_1__* mec2_fw; scalar_t__ new_fw; } ;
struct TYPE_6__ {int /*<<< orphan*/  ucode_version; int /*<<< orphan*/  ucode_size_bytes; int /*<<< orphan*/  ucode_array_offset_bytes; } ;
struct gfx_firmware_header_v1_0 {TYPE_3__ header; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ CHIP_KAVERI ; 
 int CIK_MEC_UCODE_SIZE ; 
 int /*<<< orphan*/  CP_MEC_ME1_UCODE_ADDR ; 
 int /*<<< orphan*/  CP_MEC_ME1_UCODE_DATA ; 
 int /*<<< orphan*/  CP_MEC_ME2_UCODE_ADDR ; 
 int /*<<< orphan*/  CP_MEC_ME2_UCODE_DATA ; 
 int EINVAL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cik_cp_compute_enable (struct radeon_device*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ucode_print_gfx_hdr (TYPE_3__*) ; 

__attribute__((used)) static int cik_cp_compute_load_microcode(struct radeon_device *rdev)
{
	int i;

	if (!rdev->mec_fw)
		return -EINVAL;

	cik_cp_compute_enable(rdev, false);

	if (rdev->new_fw) {
		const struct gfx_firmware_header_v1_0 *mec_hdr =
			(const struct gfx_firmware_header_v1_0 *)rdev->mec_fw->data;
		const __le32 *fw_data;
		u32 fw_size;

		radeon_ucode_print_gfx_hdr(&mec_hdr->header);

		/* MEC1 */
		fw_data = (const __le32 *)
			(rdev->mec_fw->data + le32_to_cpu(mec_hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(mec_hdr->header.ucode_size_bytes) / 4;
		WREG32(CP_MEC_ME1_UCODE_ADDR, 0);
		for (i = 0; i < fw_size; i++)
			WREG32(CP_MEC_ME1_UCODE_DATA, le32_to_cpup(fw_data++));
		WREG32(CP_MEC_ME1_UCODE_ADDR, le32_to_cpu(mec_hdr->header.ucode_version));

		/* MEC2 */
		if (rdev->family == CHIP_KAVERI) {
			const struct gfx_firmware_header_v1_0 *mec2_hdr =
				(const struct gfx_firmware_header_v1_0 *)rdev->mec2_fw->data;

			fw_data = (const __le32 *)
				(rdev->mec2_fw->data +
				 le32_to_cpu(mec2_hdr->header.ucode_array_offset_bytes));
			fw_size = le32_to_cpu(mec2_hdr->header.ucode_size_bytes) / 4;
			WREG32(CP_MEC_ME2_UCODE_ADDR, 0);
			for (i = 0; i < fw_size; i++)
				WREG32(CP_MEC_ME2_UCODE_DATA, le32_to_cpup(fw_data++));
			WREG32(CP_MEC_ME2_UCODE_ADDR, le32_to_cpu(mec2_hdr->header.ucode_version));
		}
	} else {
		const __be32 *fw_data;

		/* MEC1 */
		fw_data = (const __be32 *)rdev->mec_fw->data;
		WREG32(CP_MEC_ME1_UCODE_ADDR, 0);
		for (i = 0; i < CIK_MEC_UCODE_SIZE; i++)
			WREG32(CP_MEC_ME1_UCODE_DATA, be32_to_cpup(fw_data++));
		WREG32(CP_MEC_ME1_UCODE_ADDR, 0);

		if (rdev->family == CHIP_KAVERI) {
			/* MEC2 */
			fw_data = (const __be32 *)rdev->mec_fw->data;
			WREG32(CP_MEC_ME2_UCODE_ADDR, 0);
			for (i = 0; i < CIK_MEC_UCODE_SIZE; i++)
				WREG32(CP_MEC_ME2_UCODE_DATA, be32_to_cpup(fw_data++));
			WREG32(CP_MEC_ME2_UCODE_ADDR, 0);
		}
	}

	return 0;
}