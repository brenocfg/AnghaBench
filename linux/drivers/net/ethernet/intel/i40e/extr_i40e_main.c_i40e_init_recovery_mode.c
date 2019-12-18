#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i40e_vsi {int alloc_queue_pairs; int netdev_registered; int /*<<< orphan*/  netdev; } ;
struct TYPE_3__ {scalar_t__ num_vsis; } ;
struct TYPE_4__ {TYPE_1__ func_caps; } ;
struct i40e_pf {scalar_t__ num_alloc_vsi; int lan_vsi; int /*<<< orphan*/  pdev; int /*<<< orphan*/  service_timer; scalar_t__ service_timer_period; struct i40e_vsi** vsi; TYPE_2__ hw; int /*<<< orphan*/  state; int /*<<< orphan*/  service_task; } ;
struct i40e_hw {int /*<<< orphan*/  hw_addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HZ ; 
 scalar_t__ I40E_MIN_VSI_ALLOC ; 
 int /*<<< orphan*/  I40E_VSI_MAIN ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __I40E_SERVICE_SCHED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int i40e_config_netdev (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_dbg_pf_init (struct i40e_pf*) ; 
 int i40e_init_interrupt_scheme (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_reset_interrupt_capability (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_send_version (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_service_task ; 
 int /*<<< orphan*/  i40e_service_timer ; 
 int i40e_setup_misc_vector_for_recovery_mode (struct i40e_pf*) ; 
 int /*<<< orphan*/  i40e_shutdown_adminq (struct i40e_hw*) ; 
 int i40e_vsi_mem_alloc (struct i40e_pf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 struct i40e_vsi** kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i40e_pf*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_mem_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_save_state (int /*<<< orphan*/ ) ; 
 int register_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i40e_init_recovery_mode(struct i40e_pf *pf, struct i40e_hw *hw)
{
	struct i40e_vsi *vsi;
	int err;
	int v_idx;

	pci_save_state(pf->pdev);

	/* set up periodic task facility */
	timer_setup(&pf->service_timer, i40e_service_timer, 0);
	pf->service_timer_period = HZ;

	INIT_WORK(&pf->service_task, i40e_service_task);
	clear_bit(__I40E_SERVICE_SCHED, pf->state);

	err = i40e_init_interrupt_scheme(pf);
	if (err)
		goto err_switch_setup;

	/* The number of VSIs reported by the FW is the minimum guaranteed
	 * to us; HW supports far more and we share the remaining pool with
	 * the other PFs. We allocate space for more than the guarantee with
	 * the understanding that we might not get them all later.
	 */
	if (pf->hw.func_caps.num_vsis < I40E_MIN_VSI_ALLOC)
		pf->num_alloc_vsi = I40E_MIN_VSI_ALLOC;
	else
		pf->num_alloc_vsi = pf->hw.func_caps.num_vsis;

	/* Set up the vsi struct and our local tracking of the MAIN PF vsi. */
	pf->vsi = kcalloc(pf->num_alloc_vsi, sizeof(struct i40e_vsi *),
			  GFP_KERNEL);
	if (!pf->vsi) {
		err = -ENOMEM;
		goto err_switch_setup;
	}

	/* We allocate one VSI which is needed as absolute minimum
	 * in order to register the netdev
	 */
	v_idx = i40e_vsi_mem_alloc(pf, I40E_VSI_MAIN);
	if (v_idx < 0)
		goto err_switch_setup;
	pf->lan_vsi = v_idx;
	vsi = pf->vsi[v_idx];
	if (!vsi)
		goto err_switch_setup;
	vsi->alloc_queue_pairs = 1;
	err = i40e_config_netdev(vsi);
	if (err)
		goto err_switch_setup;
	err = register_netdev(vsi->netdev);
	if (err)
		goto err_switch_setup;
	vsi->netdev_registered = true;
	i40e_dbg_pf_init(pf);

	err = i40e_setup_misc_vector_for_recovery_mode(pf);
	if (err)
		goto err_switch_setup;

	/* tell the firmware that we're starting */
	i40e_send_version(pf);

	/* since everything's happy, start the service_task timer */
	mod_timer(&pf->service_timer,
		  round_jiffies(jiffies + pf->service_timer_period));

	return 0;

err_switch_setup:
	i40e_reset_interrupt_capability(pf);
	del_timer_sync(&pf->service_timer);
	i40e_shutdown_adminq(hw);
	iounmap(hw->hw_addr);
	pci_disable_pcie_error_reporting(pf->pdev);
	pci_release_mem_regions(pf->pdev);
	pci_disable_device(pf->pdev);
	kfree(pf);

	return err;
}