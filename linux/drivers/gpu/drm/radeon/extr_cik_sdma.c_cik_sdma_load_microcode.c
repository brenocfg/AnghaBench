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
struct TYPE_4__ {int /*<<< orphan*/  ucode_size_bytes; int /*<<< orphan*/  ucode_array_offset_bytes; } ;
struct sdma_firmware_header_v1_0 {TYPE_2__ header; } ;
struct radeon_device {TYPE_1__* sdma_fw; scalar_t__ new_fw; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int CIK_SDMA_UCODE_SIZE ; 
 int /*<<< orphan*/  CIK_SDMA_UCODE_VERSION ; 
 int EINVAL ; 
 scalar_t__ SDMA0_REGISTER_OFFSET ; 
 scalar_t__ SDMA0_UCODE_ADDR ; 
 scalar_t__ SDMA0_UCODE_DATA ; 
 scalar_t__ SDMA1_REGISTER_OFFSET ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cik_sdma_enable (struct radeon_device*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ucode_print_sdma_hdr (TYPE_2__*) ; 

__attribute__((used)) static int cik_sdma_load_microcode(struct radeon_device *rdev)
{
	int i;

	if (!rdev->sdma_fw)
		return -EINVAL;

	/* halt the MEs */
	cik_sdma_enable(rdev, false);

	if (rdev->new_fw) {
		const struct sdma_firmware_header_v1_0 *hdr =
			(const struct sdma_firmware_header_v1_0 *)rdev->sdma_fw->data;
		const __le32 *fw_data;
		u32 fw_size;

		radeon_ucode_print_sdma_hdr(&hdr->header);

		/* sdma0 */
		fw_data = (const __le32 *)
			(rdev->sdma_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
		WREG32(SDMA0_UCODE_ADDR + SDMA0_REGISTER_OFFSET, 0);
		for (i = 0; i < fw_size; i++)
			WREG32(SDMA0_UCODE_DATA + SDMA0_REGISTER_OFFSET, le32_to_cpup(fw_data++));
		WREG32(SDMA0_UCODE_DATA + SDMA0_REGISTER_OFFSET, CIK_SDMA_UCODE_VERSION);

		/* sdma1 */
		fw_data = (const __le32 *)
			(rdev->sdma_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));
		fw_size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
		WREG32(SDMA0_UCODE_ADDR + SDMA1_REGISTER_OFFSET, 0);
		for (i = 0; i < fw_size; i++)
			WREG32(SDMA0_UCODE_DATA + SDMA1_REGISTER_OFFSET, le32_to_cpup(fw_data++));
		WREG32(SDMA0_UCODE_DATA + SDMA1_REGISTER_OFFSET, CIK_SDMA_UCODE_VERSION);
	} else {
		const __be32 *fw_data;

		/* sdma0 */
		fw_data = (const __be32 *)rdev->sdma_fw->data;
		WREG32(SDMA0_UCODE_ADDR + SDMA0_REGISTER_OFFSET, 0);
		for (i = 0; i < CIK_SDMA_UCODE_SIZE; i++)
			WREG32(SDMA0_UCODE_DATA + SDMA0_REGISTER_OFFSET, be32_to_cpup(fw_data++));
		WREG32(SDMA0_UCODE_DATA + SDMA0_REGISTER_OFFSET, CIK_SDMA_UCODE_VERSION);

		/* sdma1 */
		fw_data = (const __be32 *)rdev->sdma_fw->data;
		WREG32(SDMA0_UCODE_ADDR + SDMA1_REGISTER_OFFSET, 0);
		for (i = 0; i < CIK_SDMA_UCODE_SIZE; i++)
			WREG32(SDMA0_UCODE_DATA + SDMA1_REGISTER_OFFSET, be32_to_cpup(fw_data++));
		WREG32(SDMA0_UCODE_DATA + SDMA1_REGISTER_OFFSET, CIK_SDMA_UCODE_VERSION);
	}

	WREG32(SDMA0_UCODE_ADDR + SDMA0_REGISTER_OFFSET, 0);
	WREG32(SDMA0_UCODE_ADDR + SDMA1_REGISTER_OFFSET, 0);
	return 0;
}