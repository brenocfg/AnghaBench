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
typedef  void* u8 ;
typedef  int u32 ;
struct rv7xx_power_info {void** odt_value_1; void** odt_value_0; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC4_IO_DQ_PAD_CNTL_D0_I0 ; 
 int /*<<< orphan*/  MC4_IO_QS_PAD_CNTL_D0_I0 ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

void rv730_get_odt_values(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u32 mc4_io_pad_cntl;

	pi->odt_value_0[0] = (u8)0;
	pi->odt_value_1[0] = (u8)0x80;

	mc4_io_pad_cntl = RREG32(MC4_IO_DQ_PAD_CNTL_D0_I0);
	pi->odt_value_0[1] = (u8)(mc4_io_pad_cntl & 0xff);

	mc4_io_pad_cntl = RREG32(MC4_IO_QS_PAD_CNTL_D0_I0);
	pi->odt_value_1[1] = (u8)(mc4_io_pad_cntl & 0xff);
}