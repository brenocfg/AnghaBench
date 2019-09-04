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
typedef  int fw_port_cap32_t ;

/* Variables and functions */
 int FW_PORT_CAP32_SPEED_100G ; 
 int FW_PORT_CAP32_SPEED_100M ; 
 int FW_PORT_CAP32_SPEED_10G ; 
 int FW_PORT_CAP32_SPEED_1G ; 
 int FW_PORT_CAP32_SPEED_200G ; 
 int FW_PORT_CAP32_SPEED_25G ; 
 int FW_PORT_CAP32_SPEED_400G ; 
 int FW_PORT_CAP32_SPEED_40G ; 
 int FW_PORT_CAP32_SPEED_50G ; 

__attribute__((used)) static unsigned int fwcap_to_speed(fw_port_cap32_t caps)
{
	#define TEST_SPEED_RETURN(__caps_speed, __speed) \
		do { \
			if (caps & FW_PORT_CAP32_SPEED_##__caps_speed) \
				return __speed; \
		} while (0)

	TEST_SPEED_RETURN(400G, 400000);
	TEST_SPEED_RETURN(200G, 200000);
	TEST_SPEED_RETURN(100G, 100000);
	TEST_SPEED_RETURN(50G,   50000);
	TEST_SPEED_RETURN(40G,   40000);
	TEST_SPEED_RETURN(25G,   25000);
	TEST_SPEED_RETURN(10G,   10000);
	TEST_SPEED_RETURN(1G,     1000);
	TEST_SPEED_RETURN(100M,    100);

	#undef TEST_SPEED_RETURN

	return 0;
}