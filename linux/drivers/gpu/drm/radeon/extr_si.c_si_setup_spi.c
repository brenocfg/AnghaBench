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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_STATIC_THREAD_MGMT_3 ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int si_get_cu_enabled (struct radeon_device*,int) ; 
 int /*<<< orphan*/  si_select_se_sh (struct radeon_device*,int,int) ; 

__attribute__((used)) static void si_setup_spi(struct radeon_device *rdev,
			 u32 se_num, u32 sh_per_se,
			 u32 cu_per_sh)
{
	int i, j, k;
	u32 data, mask, active_cu;

	for (i = 0; i < se_num; i++) {
		for (j = 0; j < sh_per_se; j++) {
			si_select_se_sh(rdev, i, j);
			data = RREG32(SPI_STATIC_THREAD_MGMT_3);
			active_cu = si_get_cu_enabled(rdev, cu_per_sh);

			mask = 1;
			for (k = 0; k < 16; k++) {
				mask <<= k;
				if (active_cu & mask) {
					data &= ~mask;
					WREG32(SPI_STATIC_THREAD_MGMT_3, data);
					break;
				}
			}
		}
	}
	si_select_se_sh(rdev, 0xffffffff, 0xffffffff);
}