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
struct rv7xx_power_info {scalar_t__ mem_gddr5; scalar_t__ mclk_stutter_mode_threshold; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_PMG_AUTO_CFG ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void btc_init_stutter_mode(struct radeon_device *rdev)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u32 tmp;

	if (pi->mclk_stutter_mode_threshold) {
		if (pi->mem_gddr5) {
			tmp = RREG32(MC_PMG_AUTO_CFG);
			if ((0x200 & tmp) == 0) {
				tmp = (tmp & 0xfffffc0b) | 0x204;
				WREG32(MC_PMG_AUTO_CFG, tmp);
			}
		}
	}
}