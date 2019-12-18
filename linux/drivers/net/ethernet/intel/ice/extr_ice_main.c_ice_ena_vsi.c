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
 int /*<<< orphan*/  __ICE_NEEDS_RESTART ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ice_open (scalar_t__) ; 
 scalar_t__ netif_running (scalar_t__) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_ena_vsi(struct ice_vsi *vsi, bool locked)
{
	int err = 0;

	if (!test_bit(__ICE_NEEDS_RESTART, vsi->state))
		return 0;

	clear_bit(__ICE_NEEDS_RESTART, vsi->state);

	if (vsi->netdev && vsi->type == ICE_VSI_PF) {
		if (netif_running(vsi->netdev)) {
			if (!locked)
				rtnl_lock();

			err = ice_open(vsi->netdev);

			if (!locked)
				rtnl_unlock();
		}
	}

	return err;
}