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
struct TYPE_3__ {int link_speed; } ;
struct TYPE_4__ {TYPE_1__ link_info; } ;
struct ice_port_info {TYPE_2__ phy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int,unsigned int) ; 
#define  ICE_AQ_LINK_SPEED_100GB 133 
#define  ICE_AQ_LINK_SPEED_10GB 132 
#define  ICE_AQ_LINK_SPEED_20GB 131 
#define  ICE_AQ_LINK_SPEED_25GB 130 
#define  ICE_AQ_LINK_SPEED_40GB 129 
#define  ICE_AQ_LINK_SPEED_50GB 128 
 unsigned int ICE_ITR_ADAPTIVE_LATENCY ; 
 unsigned int ICE_ITR_ADAPTIVE_MAX_USECS ; 
 unsigned int ICE_ITR_MASK ; 

__attribute__((used)) static unsigned int
ice_adjust_itr_by_size_and_speed(struct ice_port_info *port_info,
				 unsigned int avg_pkt_size,
				 unsigned int itr)
{
	switch (port_info->phy.link_info.link_speed) {
	case ICE_AQ_LINK_SPEED_100GB:
		itr += DIV_ROUND_UP(17 * (avg_pkt_size + 24),
				    avg_pkt_size + 640);
		break;
	case ICE_AQ_LINK_SPEED_50GB:
		itr += DIV_ROUND_UP(34 * (avg_pkt_size + 24),
				    avg_pkt_size + 640);
		break;
	case ICE_AQ_LINK_SPEED_40GB:
		itr += DIV_ROUND_UP(43 * (avg_pkt_size + 24),
				    avg_pkt_size + 640);
		break;
	case ICE_AQ_LINK_SPEED_25GB:
		itr += DIV_ROUND_UP(68 * (avg_pkt_size + 24),
				    avg_pkt_size + 640);
		break;
	case ICE_AQ_LINK_SPEED_20GB:
		itr += DIV_ROUND_UP(85 * (avg_pkt_size + 24),
				    avg_pkt_size + 640);
		break;
	case ICE_AQ_LINK_SPEED_10GB:
		/* fall through */
	default:
		itr += DIV_ROUND_UP(170 * (avg_pkt_size + 24),
				    avg_pkt_size + 640);
		break;
	}

	if ((itr & ICE_ITR_MASK) > ICE_ITR_ADAPTIVE_MAX_USECS) {
		itr &= ICE_ITR_ADAPTIVE_LATENCY;
		itr += ICE_ITR_ADAPTIVE_MAX_USECS;
	}

	return itr;
}