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
struct tg3 {int /*<<< orphan*/  grc_local_ctrl; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5717 ; 
 scalar_t__ ASIC_REV_5719 ; 
 scalar_t__ ASIC_REV_5720 ; 
 int EIO ; 
 int /*<<< orphan*/  GRC_LOCAL_CTRL ; 
 int /*<<< orphan*/  IS_NIC ; 
 int /*<<< orphan*/  TG3_APE_LOCK_GPIO ; 
 int /*<<< orphan*/  TG3_GPIO_MSG_DRVR_PRES ; 
 int /*<<< orphan*/  TG3_GRC_LCLCTL_PWRSW_DELAY ; 
 scalar_t__ tg3_ape_lock (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_ape_unlock (struct tg3*,int /*<<< orphan*/ ) ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 int /*<<< orphan*/  tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_set_function_status (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_wait_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int tg3_pwrsrc_switch_to_vmain(struct tg3 *tp)
{
	if (!tg3_flag(tp, IS_NIC))
		return 0;

	if (tg3_asic_rev(tp) == ASIC_REV_5717 ||
	    tg3_asic_rev(tp) == ASIC_REV_5719 ||
	    tg3_asic_rev(tp) == ASIC_REV_5720) {
		if (tg3_ape_lock(tp, TG3_APE_LOCK_GPIO))
			return -EIO;

		tg3_set_function_status(tp, TG3_GPIO_MSG_DRVR_PRES);

		tw32_wait_f(GRC_LOCAL_CTRL, tp->grc_local_ctrl,
			    TG3_GRC_LCLCTL_PWRSW_DELAY);

		tg3_ape_unlock(tp, TG3_APE_LOCK_GPIO);
	} else {
		tw32_wait_f(GRC_LOCAL_CTRL, tp->grc_local_ctrl,
			    TG3_GRC_LCLCTL_PWRSW_DELAY);
	}

	return 0;
}