#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct radeon_device {scalar_t__ family; TYPE_1__* rlc_fw; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ CHIP_RV770 ; 
 int EINVAL ; 
 scalar_t__ R600_RLC_UCODE_SIZE ; 
 scalar_t__ R700_RLC_UCODE_SIZE ; 
 int /*<<< orphan*/  RLC_HB_BASE ; 
 int /*<<< orphan*/  RLC_HB_CNTL ; 
 int /*<<< orphan*/  RLC_HB_RPTR ; 
 int /*<<< orphan*/  RLC_HB_WPTR ; 
 int /*<<< orphan*/  RLC_HB_WPTR_LSB_ADDR ; 
 int /*<<< orphan*/  RLC_HB_WPTR_MSB_ADDR ; 
 int /*<<< orphan*/  RLC_MC_CNTL ; 
 int /*<<< orphan*/  RLC_UCODE_ADDR ; 
 int /*<<< orphan*/  RLC_UCODE_CNTL ; 
 int /*<<< orphan*/  RLC_UCODE_DATA ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_rlc_start (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_rlc_stop (struct radeon_device*) ; 

__attribute__((used)) static int r600_rlc_resume(struct radeon_device *rdev)
{
	u32 i;
	const __be32 *fw_data;

	if (!rdev->rlc_fw)
		return -EINVAL;

	r600_rlc_stop(rdev);

	WREG32(RLC_HB_CNTL, 0);

	WREG32(RLC_HB_BASE, 0);
	WREG32(RLC_HB_RPTR, 0);
	WREG32(RLC_HB_WPTR, 0);
	WREG32(RLC_HB_WPTR_LSB_ADDR, 0);
	WREG32(RLC_HB_WPTR_MSB_ADDR, 0);
	WREG32(RLC_MC_CNTL, 0);
	WREG32(RLC_UCODE_CNTL, 0);

	fw_data = (const __be32 *)rdev->rlc_fw->data;
	if (rdev->family >= CHIP_RV770) {
		for (i = 0; i < R700_RLC_UCODE_SIZE; i++) {
			WREG32(RLC_UCODE_ADDR, i);
			WREG32(RLC_UCODE_DATA, be32_to_cpup(fw_data++));
		}
	} else {
		for (i = 0; i < R600_RLC_UCODE_SIZE; i++) {
			WREG32(RLC_UCODE_ADDR, i);
			WREG32(RLC_UCODE_DATA, be32_to_cpup(fw_data++));
		}
	}
	WREG32(RLC_UCODE_ADDR, 0);

	r600_rlc_start(rdev);

	return 0;
}