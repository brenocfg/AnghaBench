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
struct si_power_info {int /*<<< orphan*/  cac_weights; int /*<<< orphan*/  cac_override; int /*<<< orphan*/  lcac_config; } ;
struct radeon_device {int dummy; } ;
struct ni_power_info {int enable_cac; int cac_configuration_required; } ;

/* Variables and functions */
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 
 int si_program_cac_config_registers (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si_initialize_hardware_cac_manager(struct radeon_device *rdev)
{
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	struct si_power_info *si_pi = si_get_pi(rdev);
	int ret;

	if ((ni_pi->enable_cac == false) ||
	    (ni_pi->cac_configuration_required == false))
		return 0;

	ret = si_program_cac_config_registers(rdev, si_pi->lcac_config);
	if (ret)
		return ret;
	ret = si_program_cac_config_registers(rdev, si_pi->cac_override);
	if (ret)
		return ret;
	ret = si_program_cac_config_registers(rdev, si_pi->cac_weights);
	if (ret)
		return ret;

	return 0;
}