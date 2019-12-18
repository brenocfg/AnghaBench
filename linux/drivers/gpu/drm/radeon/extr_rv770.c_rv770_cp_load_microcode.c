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
struct radeon_device {TYPE_2__* me_fw; TYPE_1__* pfp_fw; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int BUF_SWAP_32BIT ; 
 int /*<<< orphan*/  CP_ME_RAM_DATA ; 
 int /*<<< orphan*/  CP_ME_RAM_RADDR ; 
 int /*<<< orphan*/  CP_ME_RAM_WADDR ; 
 int /*<<< orphan*/  CP_PFP_UCODE_ADDR ; 
 int /*<<< orphan*/  CP_PFP_UCODE_DATA ; 
 int /*<<< orphan*/  CP_RB_CNTL ; 
 int EINVAL ; 
 int /*<<< orphan*/  GRBM_SOFT_RESET ; 
 int R700_PFP_UCODE_SIZE ; 
 int R700_PM4_UCODE_SIZE ; 
 int RB_BLKSZ (int) ; 
 int RB_BUFSZ (int) ; 
 int RB_NO_UPDATE ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int SOFT_RESET_CP ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  r700_cp_stop (struct radeon_device*) ; 

__attribute__((used)) static int rv770_cp_load_microcode(struct radeon_device *rdev)
{
	const __be32 *fw_data;
	int i;

	if (!rdev->me_fw || !rdev->pfp_fw)
		return -EINVAL;

	r700_cp_stop(rdev);
	WREG32(CP_RB_CNTL,
#ifdef __BIG_ENDIAN
	       BUF_SWAP_32BIT |
#endif
	       RB_NO_UPDATE | RB_BLKSZ(15) | RB_BUFSZ(3));

	/* Reset cp */
	WREG32(GRBM_SOFT_RESET, SOFT_RESET_CP);
	RREG32(GRBM_SOFT_RESET);
	mdelay(15);
	WREG32(GRBM_SOFT_RESET, 0);

	fw_data = (const __be32 *)rdev->pfp_fw->data;
	WREG32(CP_PFP_UCODE_ADDR, 0);
	for (i = 0; i < R700_PFP_UCODE_SIZE; i++)
		WREG32(CP_PFP_UCODE_DATA, be32_to_cpup(fw_data++));
	WREG32(CP_PFP_UCODE_ADDR, 0);

	fw_data = (const __be32 *)rdev->me_fw->data;
	WREG32(CP_ME_RAM_WADDR, 0);
	for (i = 0; i < R700_PM4_UCODE_SIZE; i++)
		WREG32(CP_ME_RAM_DATA, be32_to_cpup(fw_data++));

	WREG32(CP_PFP_UCODE_ADDR, 0);
	WREG32(CP_ME_RAM_WADDR, 0);
	WREG32(CP_ME_RAM_RADDR, 0);
	return 0;
}