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
 int LCB_CRC_12B_16B_PER_LANE ; 
 int LCB_CRC_14B ; 
 int LCB_CRC_48B ; 
 int PORT_LTP_CRC_MODE_14 ; 
 int PORT_LTP_CRC_MODE_16 ; 
 int PORT_LTP_CRC_MODE_48 ; 
 int PORT_LTP_CRC_MODE_PER_LANE ; 

__attribute__((used)) static int lcb_to_port_ltp(int lcb_crc)
{
	int port_ltp = 0;

	if (lcb_crc == LCB_CRC_12B_16B_PER_LANE)
		port_ltp = PORT_LTP_CRC_MODE_PER_LANE;
	else if (lcb_crc == LCB_CRC_48B)
		port_ltp = PORT_LTP_CRC_MODE_48;
	else if (lcb_crc == LCB_CRC_14B)
		port_ltp = PORT_LTP_CRC_MODE_14;
	else
		port_ltp = PORT_LTP_CRC_MODE_16;

	return port_ltp;
}