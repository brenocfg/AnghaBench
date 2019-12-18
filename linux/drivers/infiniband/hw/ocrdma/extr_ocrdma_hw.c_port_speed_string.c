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
typedef  int u16 ;
struct TYPE_2__ {int fixed_speeds_supported; int auto_speeds_supported; } ;
struct ocrdma_dev {TYPE_1__ phy; } ;

/* Variables and functions */
 int OCRDMA_PHY_SPEED_10GBPS ; 
 int OCRDMA_PHY_SPEED_1GBPS ; 
 int OCRDMA_PHY_SPEED_40GBPS ; 

char *port_speed_string(struct ocrdma_dev *dev)
{
	char *str = "";
	u16 speeds_supported;

	speeds_supported = dev->phy.fixed_speeds_supported |
				dev->phy.auto_speeds_supported;
	if (speeds_supported & OCRDMA_PHY_SPEED_40GBPS)
		str = "40Gbps ";
	else if (speeds_supported & OCRDMA_PHY_SPEED_10GBPS)
		str = "10Gbps ";
	else if (speeds_supported & OCRDMA_PHY_SPEED_1GBPS)
		str = "1Gbps ";

	return str;
}