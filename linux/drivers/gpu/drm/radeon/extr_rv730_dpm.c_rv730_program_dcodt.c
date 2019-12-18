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
typedef  int u32 ;
struct rv7xx_power_info {int* odt_value_0; int* odt_value_1; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC4_IO_DQ_PAD_CNTL_D0_I0 ; 
 int /*<<< orphan*/  MC4_IO_DQ_PAD_CNTL_D0_I1 ; 
 int /*<<< orphan*/  MC4_IO_QS_PAD_CNTL_D0_I0 ; 
 int /*<<< orphan*/  MC4_IO_QS_PAD_CNTL_D0_I1 ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

void rv730_program_dcodt(struct radeon_device *rdev, bool use_dcodt)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u32 i = use_dcodt ? 0 : 1;
	u32 mc4_io_pad_cntl;

	mc4_io_pad_cntl = RREG32(MC4_IO_DQ_PAD_CNTL_D0_I0);
	mc4_io_pad_cntl &= 0xFFFFFF00;
	mc4_io_pad_cntl |= pi->odt_value_0[i];
	WREG32(MC4_IO_DQ_PAD_CNTL_D0_I0, mc4_io_pad_cntl);
	WREG32(MC4_IO_DQ_PAD_CNTL_D0_I1, mc4_io_pad_cntl);

	mc4_io_pad_cntl = RREG32(MC4_IO_QS_PAD_CNTL_D0_I0);
	mc4_io_pad_cntl &= 0xFFFFFF00;
	mc4_io_pad_cntl |= pi->odt_value_1[i];
	WREG32(MC4_IO_QS_PAD_CNTL_D0_I0, mc4_io_pad_cntl);
	WREG32(MC4_IO_QS_PAD_CNTL_D0_I1, mc4_io_pad_cntl);
}