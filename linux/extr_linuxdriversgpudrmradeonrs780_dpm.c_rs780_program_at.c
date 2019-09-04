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
struct radeon_device {int dummy; } ;
struct igp_power_info {int refresh_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  FVTHROT_CB1 ; 
 int /*<<< orphan*/  FVTHROT_CB2 ; 
 int /*<<< orphan*/  FVTHROT_CB3 ; 
 int /*<<< orphan*/  FVTHROT_CB4 ; 
 int /*<<< orphan*/  FVTHROT_TARGET_REG ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 struct igp_power_info* rs780_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void rs780_program_at(struct radeon_device *rdev)
{
	struct igp_power_info *pi = rs780_get_pi(rdev);

	WREG32(FVTHROT_TARGET_REG, 30000000 / pi->refresh_rate);
	WREG32(FVTHROT_CB1, 1000000 * 5 / pi->refresh_rate);
	WREG32(FVTHROT_CB2, 1000000 * 10 / pi->refresh_rate);
	WREG32(FVTHROT_CB3, 1000000 * 30 / pi->refresh_rate);
	WREG32(FVTHROT_CB4, 1000000 * 50 / pi->refresh_rate);
}