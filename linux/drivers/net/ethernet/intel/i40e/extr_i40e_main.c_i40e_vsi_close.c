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
struct i40e_vsi {scalar_t__ current_netdev_flags; int /*<<< orphan*/  state; struct i40e_pf* back; } ;
struct i40e_pf {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __I40E_CLIENT_RESET ; 
 int /*<<< orphan*/  __I40E_CLIENT_SERVICE_REQUESTED ; 
 int /*<<< orphan*/  __I40E_RESET_RECOVERY_PENDING ; 
 int /*<<< orphan*/  __I40E_VSI_DOWN ; 
 int /*<<< orphan*/  i40e_down (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vsi_free_irq (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vsi_free_rx_resources (struct i40e_vsi*) ; 
 int /*<<< orphan*/  i40e_vsi_free_tx_resources (struct i40e_vsi*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_vsi_close(struct i40e_vsi *vsi)
{
	struct i40e_pf *pf = vsi->back;
	if (!test_and_set_bit(__I40E_VSI_DOWN, vsi->state))
		i40e_down(vsi);
	i40e_vsi_free_irq(vsi);
	i40e_vsi_free_tx_resources(vsi);
	i40e_vsi_free_rx_resources(vsi);
	vsi->current_netdev_flags = 0;
	set_bit(__I40E_CLIENT_SERVICE_REQUESTED, pf->state);
	if (test_bit(__I40E_RESET_RECOVERY_PENDING, pf->state))
		set_bit(__I40E_CLIENT_RESET, pf->state);
}