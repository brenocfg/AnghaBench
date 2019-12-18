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
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
typedef  enum hinic_speed { ____Placeholder_hinic_speed } hinic_speed ;

/* Variables and functions */
#define  HINIC_SPEED_1000MB_LINK 134 
#define  HINIC_SPEED_100GB_LINK 133 
#define  HINIC_SPEED_100MB_LINK 132 
#define  HINIC_SPEED_10GB_LINK 131 
#define  HINIC_SPEED_10MB_LINK 130 
#define  HINIC_SPEED_25GB_LINK 129 
#define  HINIC_SPEED_40GB_LINK 128 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  SPEED_100000 ; 
 int /*<<< orphan*/  SPEED_25000 ; 
 int /*<<< orphan*/  SPEED_40000 ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 

__attribute__((used)) static void set_link_speed(struct ethtool_link_ksettings *link_ksettings,
			   enum hinic_speed speed)
{
	switch (speed) {
	case HINIC_SPEED_10MB_LINK:
		link_ksettings->base.speed = SPEED_10;
		break;

	case HINIC_SPEED_100MB_LINK:
		link_ksettings->base.speed = SPEED_100;
		break;

	case HINIC_SPEED_1000MB_LINK:
		link_ksettings->base.speed = SPEED_1000;
		break;

	case HINIC_SPEED_10GB_LINK:
		link_ksettings->base.speed = SPEED_10000;
		break;

	case HINIC_SPEED_25GB_LINK:
		link_ksettings->base.speed = SPEED_25000;
		break;

	case HINIC_SPEED_40GB_LINK:
		link_ksettings->base.speed = SPEED_40000;
		break;

	case HINIC_SPEED_100GB_LINK:
		link_ksettings->base.speed = SPEED_100000;
		break;

	default:
		link_ksettings->base.speed = SPEED_UNKNOWN;
		break;
	}
}