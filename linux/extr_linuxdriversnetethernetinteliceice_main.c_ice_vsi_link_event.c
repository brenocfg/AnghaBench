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
struct ice_vsi {scalar_t__ type; int /*<<< orphan*/  netdev; TYPE_2__* back; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ICE_VSI_PF ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_vsi_link_event(struct ice_vsi *vsi, bool link_up)
{
	if (!vsi || test_bit(__ICE_DOWN, vsi->state))
		return;

	if (vsi->type == ICE_VSI_PF) {
		if (!vsi->netdev) {
			dev_dbg(&vsi->back->pdev->dev,
				"vsi->netdev is not initialized!\n");
			return;
		}
		if (link_up) {
			netif_carrier_on(vsi->netdev);
			netif_tx_wake_all_queues(vsi->netdev);
		} else {
			netif_carrier_off(vsi->netdev);
			netif_tx_stop_all_queues(vsi->netdev);
		}
	}
}