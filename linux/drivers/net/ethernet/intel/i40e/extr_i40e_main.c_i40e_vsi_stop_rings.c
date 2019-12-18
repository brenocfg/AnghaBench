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
struct i40e_vsi {TYPE_1__* back; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __I40E_PORT_SUSPENDED ; 
 int /*<<< orphan*/  i40e_vsi_control_rx (struct i40e_vsi*,int) ; 
 int /*<<< orphan*/  i40e_vsi_control_tx (struct i40e_vsi*,int) ; 
 void i40e_vsi_stop_rings_no_wait (struct i40e_vsi*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i40e_vsi_stop_rings(struct i40e_vsi *vsi)
{
	/* When port TX is suspended, don't wait */
	if (test_bit(__I40E_PORT_SUSPENDED, vsi->back->state))
		return i40e_vsi_stop_rings_no_wait(vsi);

	/* do rx first for enable and last for disable
	 * Ignore return value, we need to shutdown whatever we can
	 */
	i40e_vsi_control_tx(vsi, false);
	i40e_vsi_control_rx(vsi, false);
}