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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;
struct ci_power_info {scalar_t__ caps_tcp_ramping; scalar_t__ caps_td_ramping; scalar_t__ caps_db_ramping; scalar_t__ caps_sq_ramping; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIDT_CTRL_EN ; 
 int /*<<< orphan*/  DIDT_DB_CTRL0 ; 
 int /*<<< orphan*/  DIDT_SQ_CTRL0 ; 
 int /*<<< orphan*/  DIDT_TCP_CTRL0 ; 
 int /*<<< orphan*/  DIDT_TD_CTRL0 ; 
 int /*<<< orphan*/  RREG32_DIDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_DIDT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void ci_do_enable_didt(struct radeon_device *rdev, const bool enable)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	u32 data;

	if (pi->caps_sq_ramping) {
		data = RREG32_DIDT(DIDT_SQ_CTRL0);
		if (enable)
			data |= DIDT_CTRL_EN;
		else
			data &= ~DIDT_CTRL_EN;
		WREG32_DIDT(DIDT_SQ_CTRL0, data);
	}

	if (pi->caps_db_ramping) {
		data = RREG32_DIDT(DIDT_DB_CTRL0);
		if (enable)
			data |= DIDT_CTRL_EN;
		else
			data &= ~DIDT_CTRL_EN;
		WREG32_DIDT(DIDT_DB_CTRL0, data);
	}

	if (pi->caps_td_ramping) {
		data = RREG32_DIDT(DIDT_TD_CTRL0);
		if (enable)
			data |= DIDT_CTRL_EN;
		else
			data &= ~DIDT_CTRL_EN;
		WREG32_DIDT(DIDT_TD_CTRL0, data);
	}

	if (pi->caps_tcp_ramping) {
		data = RREG32_DIDT(DIDT_TCP_CTRL0);
		if (enable)
			data |= DIDT_CTRL_EN;
		else
			data &= ~DIDT_CTRL_EN;
		WREG32_DIDT(DIDT_TCP_CTRL0, data);
	}
}