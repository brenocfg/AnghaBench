#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ice_vsi {int /*<<< orphan*/  netdev; TYPE_3__* port_info; } ;
struct TYPE_4__ {int topo_media_conflict; } ;
struct TYPE_5__ {TYPE_1__ link_info; } ;
struct TYPE_6__ {TYPE_2__ phy; } ;

/* Variables and functions */
#define  ICE_AQ_LINK_MEDIA_CONFLICT 129 
#define  ICE_AQ_LINK_TOPO_CONFLICT 128 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ice_print_topo_conflict(struct ice_vsi *vsi)
{
	switch (vsi->port_info->phy.link_info.topo_media_conflict) {
	case ICE_AQ_LINK_TOPO_CONFLICT:
	case ICE_AQ_LINK_MEDIA_CONFLICT:
		netdev_info(vsi->netdev, "Possible mis-configuration of the Ethernet port detected, please use the Intel(R) Ethernet Port Configuration Tool application to address the issue.\n");
		break;
	default:
		break;
	}
}