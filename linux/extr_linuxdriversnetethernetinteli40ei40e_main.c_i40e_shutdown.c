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
struct pci_dev {int dummy; } ;
struct i40e_hw {int dummy; } ;
struct i40e_pf {size_t lan_vsi; int hw_features; scalar_t__ wol_en; int /*<<< orphan*/ * vsi; int /*<<< orphan*/  service_task; int /*<<< orphan*/  service_timer; int /*<<< orphan*/  state; struct i40e_hw hw; } ;

/* Variables and functions */
 int I40E_HW_WOL_MC_MAGIC_PKT_WAKE ; 
 int /*<<< orphan*/  I40E_PFPM_APM ; 
 int /*<<< orphan*/  I40E_PFPM_APM_APME_MASK ; 
 int /*<<< orphan*/  I40E_PFPM_WUFC ; 
 int /*<<< orphan*/  I40E_PFPM_WUFC_MAG_MASK ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 scalar_t__ SYSTEM_POWER_OFF ; 
 int /*<<< orphan*/  __I40E_DOWN ; 
 int /*<<< orphan*/  __I40E_SUSPENDED ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_clear_interrupt_scheme (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_cloud_filter_exit (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_enable_mc_magic_wake (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_fdir_teardown (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_notify_client_of_netdev_close (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i40e_prep_for_reset (struct i40e_pf*,int) ; 
 struct i40e_pf* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_wake_from_d3 (struct pci_dev*,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ system_state ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_shutdown(struct pci_dev *pdev)
{
	struct i40e_pf *pf = pci_get_drvdata(pdev);
	struct i40e_hw *hw = &pf->hw;

	set_bit(__I40E_SUSPENDED, pf->state);
	set_bit(__I40E_DOWN, pf->state);

	del_timer_sync(&pf->service_timer);
	cancel_work_sync(&pf->service_task);
	i40e_cloud_filter_exit(pf);
	i40e_fdir_teardown(pf);

	/* Client close must be called explicitly here because the timer
	 * has been stopped.
	 */
	i40e_notify_client_of_netdev_close(pf->vsi[pf->lan_vsi], false);

	if (pf->wol_en && (pf->hw_features & I40E_HW_WOL_MC_MAGIC_PKT_WAKE))
		i40e_enable_mc_magic_wake(pf);

	i40e_prep_for_reset(pf, false);

	wr32(hw, I40E_PFPM_APM,
	     (pf->wol_en ? I40E_PFPM_APM_APME_MASK : 0));
	wr32(hw, I40E_PFPM_WUFC,
	     (pf->wol_en ? I40E_PFPM_WUFC_MAG_MASK : 0));

	i40e_clear_interrupt_scheme(pf);

	if (system_state == SYSTEM_POWER_OFF) {
		pci_wake_from_d3(pdev, pf->wol_en);
		pci_set_power_state(pdev, PCI_D3hot);
	}
}