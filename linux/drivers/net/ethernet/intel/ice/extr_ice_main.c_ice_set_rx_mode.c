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
struct net_device {int dummy; } ;
struct ice_vsi {TYPE_1__* back; int /*<<< orphan*/  flags; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_FLAG_FLTR_SYNC ; 
 int /*<<< orphan*/  ICE_VSI_FLAG_MMAC_FLTR_CHANGED ; 
 int /*<<< orphan*/  ICE_VSI_FLAG_UMAC_FLTR_CHANGED ; 
 int /*<<< orphan*/  ice_service_task_schedule (TYPE_1__*) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ice_set_rx_mode(struct net_device *netdev)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_vsi *vsi = np->vsi;

	if (!vsi)
		return;

	/* Set the flags to synchronize filters
	 * ndo_set_rx_mode may be triggered even without a change in netdev
	 * flags
	 */
	set_bit(ICE_VSI_FLAG_UMAC_FLTR_CHANGED, vsi->flags);
	set_bit(ICE_VSI_FLAG_MMAC_FLTR_CHANGED, vsi->flags);
	set_bit(ICE_FLAG_FLTR_SYNC, vsi->back->flags);

	/* schedule our worker thread which will take care of
	 * applying the new filter changes
	 */
	ice_service_task_schedule(vsi->back);
}