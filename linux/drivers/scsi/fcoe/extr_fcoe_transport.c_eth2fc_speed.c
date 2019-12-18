#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ eth_port_speed; scalar_t__ fc_port_speed; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ FC_PORTSPEED_UNKNOWN ; 
 TYPE_1__* fcoe_port_speed_mapping ; 

__attribute__((used)) static inline u32 eth2fc_speed(u32 eth_port_speed)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(fcoe_port_speed_mapping); i++) {
		if (fcoe_port_speed_mapping[i].eth_port_speed == eth_port_speed)
			return fcoe_port_speed_mapping[i].fc_port_speed;
	}

	return FC_PORTSPEED_UNKNOWN;
}