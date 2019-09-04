#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ice_vsi {int current_isup; int /*<<< orphan*/  netdev; TYPE_4__* port_info; } ;
struct TYPE_7__ {int current_mode; } ;
struct TYPE_5__ {int link_speed; } ;
struct TYPE_6__ {TYPE_1__ link_info; } ;
struct TYPE_8__ {TYPE_3__ fc; TYPE_2__ phy; } ;

/* Variables and functions */
#define  ICE_AQ_LINK_SPEED_1000MB 138 
#define  ICE_AQ_LINK_SPEED_100MB 137 
#define  ICE_AQ_LINK_SPEED_10GB 136 
#define  ICE_AQ_LINK_SPEED_20GB 135 
#define  ICE_AQ_LINK_SPEED_2500MB 134 
#define  ICE_AQ_LINK_SPEED_25GB 133 
#define  ICE_AQ_LINK_SPEED_40GB 132 
#define  ICE_AQ_LINK_SPEED_5GB 131 
#define  ICE_FC_FULL 130 
#define  ICE_FC_RX_PAUSE 129 
#define  ICE_FC_TX_PAUSE 128 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,...) ; 

void ice_print_link_msg(struct ice_vsi *vsi, bool isup)
{
	const char *speed;
	const char *fc;

	if (vsi->current_isup == isup)
		return;

	vsi->current_isup = isup;

	if (!isup) {
		netdev_info(vsi->netdev, "NIC Link is Down\n");
		return;
	}

	switch (vsi->port_info->phy.link_info.link_speed) {
	case ICE_AQ_LINK_SPEED_40GB:
		speed = "40 G";
		break;
	case ICE_AQ_LINK_SPEED_25GB:
		speed = "25 G";
		break;
	case ICE_AQ_LINK_SPEED_20GB:
		speed = "20 G";
		break;
	case ICE_AQ_LINK_SPEED_10GB:
		speed = "10 G";
		break;
	case ICE_AQ_LINK_SPEED_5GB:
		speed = "5 G";
		break;
	case ICE_AQ_LINK_SPEED_2500MB:
		speed = "2.5 G";
		break;
	case ICE_AQ_LINK_SPEED_1000MB:
		speed = "1 G";
		break;
	case ICE_AQ_LINK_SPEED_100MB:
		speed = "100 M";
		break;
	default:
		speed = "Unknown";
		break;
	}

	switch (vsi->port_info->fc.current_mode) {
	case ICE_FC_FULL:
		fc = "RX/TX";
		break;
	case ICE_FC_TX_PAUSE:
		fc = "TX";
		break;
	case ICE_FC_RX_PAUSE:
		fc = "RX";
		break;
	default:
		fc = "Unknown";
		break;
	}

	netdev_info(vsi->netdev, "NIC Link is up %sbps, Flow Control: %s\n",
		    speed, fc);
}