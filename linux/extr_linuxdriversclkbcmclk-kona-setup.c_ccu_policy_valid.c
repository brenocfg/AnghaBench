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
struct bcm_policy_ctl {int /*<<< orphan*/  ac_bit; int /*<<< orphan*/  atl_bit; int /*<<< orphan*/  go_bit; } ;
struct bcm_lvm_en {int /*<<< orphan*/  bit; } ;
struct ccu_policy {struct bcm_policy_ctl control; struct bcm_lvm_en enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  bit_posn_valid (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static bool
ccu_policy_valid(struct ccu_policy *ccu_policy, const char *ccu_name)
{
	struct bcm_lvm_en *enable = &ccu_policy->enable;
	struct bcm_policy_ctl *control;

	if (!bit_posn_valid(enable->bit, "policy enable", ccu_name))
		return false;

	control = &ccu_policy->control;
	if (!bit_posn_valid(control->go_bit, "policy control GO", ccu_name))
		return false;

	if (!bit_posn_valid(control->atl_bit, "policy control ATL", ccu_name))
		return false;

	if (!bit_posn_valid(control->ac_bit, "policy control AC", ccu_name))
		return false;

	return true;
}