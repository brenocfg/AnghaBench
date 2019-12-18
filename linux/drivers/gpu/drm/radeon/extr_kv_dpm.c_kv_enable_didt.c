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
struct kv_power_info {scalar_t__ caps_tcp_ramping; scalar_t__ caps_td_ramping; scalar_t__ caps_db_ramping; scalar_t__ caps_sq_ramping; } ;

/* Variables and functions */
 int /*<<< orphan*/  cik_enter_rlc_safe_mode (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_exit_rlc_safe_mode (struct radeon_device*) ; 
 int /*<<< orphan*/  didt_config_kv ; 
 int /*<<< orphan*/  kv_do_enable_didt (struct radeon_device*,int) ; 
 struct kv_power_info* kv_get_pi (struct radeon_device*) ; 
 int kv_program_pt_config_registers (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kv_enable_didt(struct radeon_device *rdev, bool enable)
{
	struct kv_power_info *pi = kv_get_pi(rdev);
	int ret;

	if (pi->caps_sq_ramping ||
	    pi->caps_db_ramping ||
	    pi->caps_td_ramping ||
	    pi->caps_tcp_ramping) {
		cik_enter_rlc_safe_mode(rdev);

		if (enable) {
			ret = kv_program_pt_config_registers(rdev, didt_config_kv);
			if (ret) {
				cik_exit_rlc_safe_mode(rdev);
				return ret;
			}
		}

		kv_do_enable_didt(rdev, enable);

		cik_exit_rlc_safe_mode(rdev);
	}

	return 0;
}