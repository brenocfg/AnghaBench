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
struct ice_vsi {scalar_t__ type; TYPE_2__* netdev; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {TYPE_1__* netdev_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* ndo_stop ) (TYPE_2__*) ;} ;

/* Variables and functions */
 scalar_t__ ICE_VSI_PF ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  __ICE_NEEDS_RESTART ; 
 int /*<<< orphan*/  ice_vsi_close (struct ice_vsi*) ; 
 scalar_t__ netif_running (TYPE_2__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_dis_vsi(struct ice_vsi *vsi)
{
	if (test_bit(__ICE_DOWN, vsi->state))
		return;

	set_bit(__ICE_NEEDS_RESTART, vsi->state);

	if (vsi->netdev && netif_running(vsi->netdev) &&
	    vsi->type == ICE_VSI_PF)
		vsi->netdev->netdev_ops->ndo_stop(vsi->netdev);

	ice_vsi_close(vsi);
}