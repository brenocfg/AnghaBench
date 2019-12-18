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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;

/* Variables and functions */
#define  ICE_AQ_LINK_SPEED_1000MB 138 
#define  ICE_AQ_LINK_SPEED_100GB 137 
#define  ICE_AQ_LINK_SPEED_100MB 136 
#define  ICE_AQ_LINK_SPEED_10GB 135 
#define  ICE_AQ_LINK_SPEED_10MB 134 
#define  ICE_AQ_LINK_SPEED_20GB 133 
#define  ICE_AQ_LINK_SPEED_2500MB 132 
#define  ICE_AQ_LINK_SPEED_25GB 131 
#define  ICE_AQ_LINK_SPEED_40GB 130 
#define  ICE_AQ_LINK_SPEED_50GB 129 
#define  ICE_AQ_LINK_SPEED_5GB 128 
 int /*<<< orphan*/  ICE_LINK_SPEED_100000MBPS ; 
 int /*<<< orphan*/  ICE_LINK_SPEED_10000MBPS ; 
 int /*<<< orphan*/  ICE_LINK_SPEED_1000MBPS ; 
 int /*<<< orphan*/  ICE_LINK_SPEED_100MBPS ; 
 int /*<<< orphan*/  ICE_LINK_SPEED_10MBPS ; 
 int /*<<< orphan*/  ICE_LINK_SPEED_20000MBPS ; 
 int /*<<< orphan*/  ICE_LINK_SPEED_25000MBPS ; 
 int /*<<< orphan*/  ICE_LINK_SPEED_2500MBPS ; 
 int /*<<< orphan*/  ICE_LINK_SPEED_40000MBPS ; 
 int /*<<< orphan*/  ICE_LINK_SPEED_50000MBPS ; 
 int /*<<< orphan*/  ICE_LINK_SPEED_5000MBPS ; 
 int /*<<< orphan*/  ICE_LINK_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  VIRTCHNL_LINK_SPEED_100MB ; 
 int /*<<< orphan*/  VIRTCHNL_LINK_SPEED_10GB ; 
 int /*<<< orphan*/  VIRTCHNL_LINK_SPEED_1GB ; 
 int /*<<< orphan*/  VIRTCHNL_LINK_SPEED_20GB ; 
 int /*<<< orphan*/  VIRTCHNL_LINK_SPEED_25GB ; 
 int /*<<< orphan*/  VIRTCHNL_LINK_SPEED_40GB ; 
 int /*<<< orphan*/  VIRTCHNL_LINK_SPEED_UNKNOWN ; 

u32 ice_conv_link_speed_to_virtchnl(bool adv_link_support, u16 link_speed)
{
	u32 speed;

	if (adv_link_support)
		switch (link_speed) {
		case ICE_AQ_LINK_SPEED_10MB:
			speed = ICE_LINK_SPEED_10MBPS;
			break;
		case ICE_AQ_LINK_SPEED_100MB:
			speed = ICE_LINK_SPEED_100MBPS;
			break;
		case ICE_AQ_LINK_SPEED_1000MB:
			speed = ICE_LINK_SPEED_1000MBPS;
			break;
		case ICE_AQ_LINK_SPEED_2500MB:
			speed = ICE_LINK_SPEED_2500MBPS;
			break;
		case ICE_AQ_LINK_SPEED_5GB:
			speed = ICE_LINK_SPEED_5000MBPS;
			break;
		case ICE_AQ_LINK_SPEED_10GB:
			speed = ICE_LINK_SPEED_10000MBPS;
			break;
		case ICE_AQ_LINK_SPEED_20GB:
			speed = ICE_LINK_SPEED_20000MBPS;
			break;
		case ICE_AQ_LINK_SPEED_25GB:
			speed = ICE_LINK_SPEED_25000MBPS;
			break;
		case ICE_AQ_LINK_SPEED_40GB:
			speed = ICE_LINK_SPEED_40000MBPS;
			break;
		case ICE_AQ_LINK_SPEED_50GB:
			speed = ICE_LINK_SPEED_50000MBPS;
			break;
		case ICE_AQ_LINK_SPEED_100GB:
			speed = ICE_LINK_SPEED_100000MBPS;
			break;
		default:
			speed = ICE_LINK_SPEED_UNKNOWN;
			break;
		}
	else
		/* Virtchnl speeds are not defined for every speed supported in
		 * the hardware. To maintain compatibility with older AVF
		 * drivers, while reporting the speed the new speed values are
		 * resolved to the closest known virtchnl speeds
		 */
		switch (link_speed) {
		case ICE_AQ_LINK_SPEED_10MB:
		case ICE_AQ_LINK_SPEED_100MB:
			speed = (u32)VIRTCHNL_LINK_SPEED_100MB;
			break;
		case ICE_AQ_LINK_SPEED_1000MB:
		case ICE_AQ_LINK_SPEED_2500MB:
		case ICE_AQ_LINK_SPEED_5GB:
			speed = (u32)VIRTCHNL_LINK_SPEED_1GB;
			break;
		case ICE_AQ_LINK_SPEED_10GB:
			speed = (u32)VIRTCHNL_LINK_SPEED_10GB;
			break;
		case ICE_AQ_LINK_SPEED_20GB:
			speed = (u32)VIRTCHNL_LINK_SPEED_20GB;
			break;
		case ICE_AQ_LINK_SPEED_25GB:
			speed = (u32)VIRTCHNL_LINK_SPEED_25GB;
			break;
		case ICE_AQ_LINK_SPEED_40GB:
			/* fall through */
		case ICE_AQ_LINK_SPEED_50GB:
			/* fall through */
		case ICE_AQ_LINK_SPEED_100GB:
			speed = (u32)VIRTCHNL_LINK_SPEED_40GB;
			break;
		default:
			speed = (u32)VIRTCHNL_LINK_SPEED_UNKNOWN;
			break;
		}

	return speed;
}