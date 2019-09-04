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
 unsigned int FW_PORT_CAP32_SPEED_100G ; 
 unsigned int FW_PORT_CAP32_SPEED_100M ; 
 unsigned int FW_PORT_CAP32_SPEED_10G ; 
 unsigned int FW_PORT_CAP32_SPEED_1G ; 
 unsigned int FW_PORT_CAP32_SPEED_200G ; 
 unsigned int FW_PORT_CAP32_SPEED_25G ; 
 unsigned int FW_PORT_CAP32_SPEED_400G ; 
 unsigned int FW_PORT_CAP32_SPEED_40G ; 
 unsigned int FW_PORT_CAP32_SPEED_50G ; 

__attribute__((used)) static unsigned int speed_to_fw_caps(int speed)
{
	if (speed == 100)
		return FW_PORT_CAP32_SPEED_100M;
	if (speed == 1000)
		return FW_PORT_CAP32_SPEED_1G;
	if (speed == 10000)
		return FW_PORT_CAP32_SPEED_10G;
	if (speed == 25000)
		return FW_PORT_CAP32_SPEED_25G;
	if (speed == 40000)
		return FW_PORT_CAP32_SPEED_40G;
	if (speed == 50000)
		return FW_PORT_CAP32_SPEED_50G;
	if (speed == 100000)
		return FW_PORT_CAP32_SPEED_100G;
	if (speed == 200000)
		return FW_PORT_CAP32_SPEED_200G;
	if (speed == 400000)
		return FW_PORT_CAP32_SPEED_400G;
	return 0;
}