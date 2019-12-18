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

/* Variables and functions */
 int CAP_CRC_12B_16B_PER_LANE ; 
 int CAP_CRC_14B ; 
 int CAP_CRC_48B ; 
 int PORT_LTP_CRC_MODE_14 ; 
 int PORT_LTP_CRC_MODE_48 ; 
 int PORT_LTP_CRC_MODE_PER_LANE ; 

int port_ltp_to_cap(int port_ltp)
{
	int cap_mask = 0;

	if (port_ltp & PORT_LTP_CRC_MODE_14)
		cap_mask |= CAP_CRC_14B;
	if (port_ltp & PORT_LTP_CRC_MODE_48)
		cap_mask |= CAP_CRC_48B;
	if (port_ltp & PORT_LTP_CRC_MODE_PER_LANE)
		cap_mask |= CAP_CRC_12B_16B_PER_LANE;

	return cap_mask;
}