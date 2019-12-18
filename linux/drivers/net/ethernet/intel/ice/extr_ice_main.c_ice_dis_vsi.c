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
struct ice_vsi {scalar_t__ type; scalar_t__ netdev; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ ICE_VSI_PF ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  __ICE_NEEDS_RESTART ; 
 int /*<<< orphan*/  ice_stop (scalar_t__) ; 
 int /*<<< orphan*/  ice_vsi_close (struct ice_vsi*) ; 
 scalar_t__ netif_running (scalar_t__) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_dis_vsi(struct ice_vsi *vsi, bool locked)
{
	if (test_bit(__ICE_DOWN, vsi->state))
		return;

	set_bit(__ICE_NEEDS_RESTART, vsi->state);

	if (vsi->type == ICE_VSI_PF && vsi->netdev) {
		if (netif_running(vsi->netdev)) {
			if (!locked)
				rtnl_lock();

			ice_stop(vsi->netdev);

			if (!locked)
				rtnl_unlock();
		} else {
			ice_vsi_close(vsi);
		}
	}
}