#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i40e_vsi {TYPE_2__* netdev; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {TYPE_1__* netdev_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ndo_open ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __I40E_VSI_NEEDS_RESTART ; 
 int /*<<< orphan*/  i40e_vsi_open (struct i40e_vsi*) ; 
 scalar_t__ netif_running (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40e_unquiesce_vsi(struct i40e_vsi *vsi)
{
	if (!test_and_clear_bit(__I40E_VSI_NEEDS_RESTART, vsi->state))
		return;

	if (vsi->netdev && netif_running(vsi->netdev))
		vsi->netdev->netdev_ops->ndo_open(vsi->netdev);
	else
		i40e_vsi_open(vsi);   /* this clears the DOWN bit */
}