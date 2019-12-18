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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/  ucode_version; int /*<<< orphan*/  ucode_size_bytes; int /*<<< orphan*/  ucode_array_offset_bytes; } ;
struct rlc_firmware_header_v1_0 {TYPE_2__ header; } ;
struct radeon_device {int family; TYPE_1__* rlc_fw; scalar_t__ new_fw; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ BONAIRE_RLC_UCODE_SIZE ; 
#define  CHIP_BONAIRE 132 
#define  CHIP_HAWAII 131 
#define  CHIP_KABINI 130 
#define  CHIP_KAVERI 129 
#define  CHIP_MULLINS 128 
 int EINVAL ; 
 scalar_t__ KB_RLC_UCODE_SIZE ; 
 scalar_t__ KV_RLC_UCODE_SIZE ; 
 scalar_t__ ML_RLC_UCODE_SIZE ; 
 int /*<<< orphan*/  RLC_CGCG_CGLS_CTRL ; 
 int /*<<< orphan*/  RLC_DRIVER_DMA_STATUS ; 
 int /*<<< orphan*/  RLC_GPM_UCODE_ADDR ; 
 int /*<<< orphan*/  RLC_GPM_UCODE_DATA ; 
 int /*<<< orphan*/  RLC_LB_CNTL ; 
 int /*<<< orphan*/  RLC_LB_CNTR_INIT ; 
 int /*<<< orphan*/  RLC_LB_CNTR_MAX ; 
 int /*<<< orphan*/  RLC_LB_INIT_CU_MASK ; 
 int /*<<< orphan*/  RLC_LB_PARAMS ; 
 int /*<<< orphan*/  RLC_MC_CNTL ; 
 int /*<<< orphan*/  RLC_UCODE_CNTL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cik_enable_lbpw (struct radeon_device*,int) ; 
 int /*<<< orphan*/  cik_init_cg (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_init_pg (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_rlc_start (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_rlc_stop (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_select_se_sh (struct radeon_device*,int,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_ucode_print_rlc_hdr (TYPE_2__*) ; 
 int /*<<< orphan*/  si_rlc_reset (struct radeon_device*) ; 

__attribute__((used)) static int cik_rlc_resume(struct radeon_device *rdev)
{
	u32 i, size, tmp;

	if (!rdev->rlc_fw)
		return -EINVAL;

	cik_rlc_stop(rdev);

	/* disable CG */
	tmp = RREG32(RLC_CGCG_CGLS_CTRL) & 0xfffffffc;
	WREG32(RLC_CGCG_CGLS_CTRL, tmp);

	si_rlc_reset(rdev);

	cik_init_pg(rdev);

	cik_init_cg(rdev);

	WREG32(RLC_LB_CNTR_INIT, 0);
	WREG32(RLC_LB_CNTR_MAX, 0x00008000);

	cik_select_se_sh(rdev, 0xffffffff, 0xffffffff);
	WREG32(RLC_LB_INIT_CU_MASK, 0xffffffff);
	WREG32(RLC_LB_PARAMS, 0x00600408);
	WREG32(RLC_LB_CNTL, 0x80000004);

	WREG32(RLC_MC_CNTL, 0);
	WREG32(RLC_UCODE_CNTL, 0);

	if (rdev->new_fw) {
		const struct rlc_firmware_header_v1_0 *hdr =
			(const struct rlc_firmware_header_v1_0 *)rdev->rlc_fw->data;
		const __le32 *fw_data = (const __le32 *)
			(rdev->rlc_fw->data + le32_to_cpu(hdr->header.ucode_array_offset_bytes));

		radeon_ucode_print_rlc_hdr(&hdr->header);

		size = le32_to_cpu(hdr->header.ucode_size_bytes) / 4;
		WREG32(RLC_GPM_UCODE_ADDR, 0);
		for (i = 0; i < size; i++)
			WREG32(RLC_GPM_UCODE_DATA, le32_to_cpup(fw_data++));
		WREG32(RLC_GPM_UCODE_ADDR, le32_to_cpu(hdr->header.ucode_version));
	} else {
		const __be32 *fw_data;

		switch (rdev->family) {
		case CHIP_BONAIRE:
		case CHIP_HAWAII:
		default:
			size = BONAIRE_RLC_UCODE_SIZE;
			break;
		case CHIP_KAVERI:
			size = KV_RLC_UCODE_SIZE;
			break;
		case CHIP_KABINI:
			size = KB_RLC_UCODE_SIZE;
			break;
		case CHIP_MULLINS:
			size = ML_RLC_UCODE_SIZE;
			break;
		}

		fw_data = (const __be32 *)rdev->rlc_fw->data;
		WREG32(RLC_GPM_UCODE_ADDR, 0);
		for (i = 0; i < size; i++)
			WREG32(RLC_GPM_UCODE_DATA, be32_to_cpup(fw_data++));
		WREG32(RLC_GPM_UCODE_ADDR, 0);
	}

	/* XXX - find out what chips support lbpw */
	cik_enable_lbpw(rdev, false);

	if (rdev->family == CHIP_BONAIRE)
		WREG32(RLC_DRIVER_DMA_STATUS, 0);

	cik_rlc_start(rdev);

	return 0;
}