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
struct i40e_vsi {scalar_t__ netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40e_set_rx_mode (scalar_t__) ; 

__attribute__((used)) static void i40e_set_vsi_rx_mode(struct i40e_vsi *vsi)
{
	if (vsi->netdev)
		i40e_set_rx_mode(vsi->netdev);
}