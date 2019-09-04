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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ BASE_RX_PORTID ; 
 scalar_t__ BASE_TX_PORTID ; 

__attribute__((used)) static inline u8 hw_port_id_to_sw_port_id(u8 major, u8 hw_port_id)
{
	u8 sw_port_id = 0;

	if (hw_port_id >= BASE_TX_PORTID)
		sw_port_id = hw_port_id - BASE_TX_PORTID;
	else if (hw_port_id >= BASE_RX_PORTID)
		sw_port_id = hw_port_id - BASE_RX_PORTID;
	else
		sw_port_id = 0;

	return sw_port_id;
}