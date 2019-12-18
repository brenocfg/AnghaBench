#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct iwl_tt_mgmt {scalar_t__ state; int ct_kill_toggle; int /*<<< orphan*/  ct_kill_exit_tm; } ;
struct iwl_priv {struct iwl_tt_mgmt thermal_throttle; int /*<<< orphan*/  trans; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int /*<<< orphan*/  ct_kill_exit_tm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1 ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_CLR ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT ; 
 int /*<<< orphan*/  CSR_UCODE_DRV_GP1_SET ; 
 int CT_KILL_EXIT_DURATION ; 
 int HZ ; 
 int /*<<< orphan*/  IWL_DEBUG_TEMP (struct iwl_priv*,char*) ; 
 scalar_t__ IWL_TI_CT_KILL ; 
 int /*<<< orphan*/  STATUS_EXIT_PENDING ; 
 struct iwl_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_trans_grab_nic_access (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  iwl_trans_release_nic_access (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  iwl_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct iwl_priv* priv ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ thermal_throttle ; 

__attribute__((used)) static void iwl_tt_check_exit_ct_kill(struct timer_list *t)
{
	struct iwl_priv *priv = from_timer(priv, t,
					   thermal_throttle.ct_kill_exit_tm);
	struct iwl_tt_mgmt *tt = &priv->thermal_throttle;
	unsigned long flags;

	if (test_bit(STATUS_EXIT_PENDING, &priv->status))
		return;

	if (tt->state == IWL_TI_CT_KILL) {
		if (priv->thermal_throttle.ct_kill_toggle) {
			iwl_write32(priv->trans, CSR_UCODE_DRV_GP1_CLR,
				    CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT);
			priv->thermal_throttle.ct_kill_toggle = false;
		} else {
			iwl_write32(priv->trans, CSR_UCODE_DRV_GP1_SET,
				    CSR_UCODE_DRV_GP1_REG_BIT_CT_KILL_EXIT);
			priv->thermal_throttle.ct_kill_toggle = true;
		}
		iwl_read32(priv->trans, CSR_UCODE_DRV_GP1);
		if (iwl_trans_grab_nic_access(priv->trans, &flags))
			iwl_trans_release_nic_access(priv->trans, &flags);

		/* Reschedule the ct_kill timer to occur in
		 * CT_KILL_EXIT_DURATION seconds to ensure we get a
		 * thermal update */
		IWL_DEBUG_TEMP(priv, "schedule ct_kill exit timer\n");
		mod_timer(&priv->thermal_throttle.ct_kill_exit_tm,
			  jiffies + CT_KILL_EXIT_DURATION * HZ);
	}
}