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
 int EINVAL ; 
 int HCLGE_MAC_SPEED_100G ; 
 int HCLGE_MAC_SPEED_100M ; 
 int HCLGE_MAC_SPEED_10G ; 
 int HCLGE_MAC_SPEED_10M ; 
 int HCLGE_MAC_SPEED_1G ; 
 int HCLGE_MAC_SPEED_25G ; 
 int HCLGE_MAC_SPEED_40G ; 
 int HCLGE_MAC_SPEED_50G ; 

__attribute__((used)) static int hclge_parse_speed(int speed_cmd, int *speed)
{
	switch (speed_cmd) {
	case 6:
		*speed = HCLGE_MAC_SPEED_10M;
		break;
	case 7:
		*speed = HCLGE_MAC_SPEED_100M;
		break;
	case 0:
		*speed = HCLGE_MAC_SPEED_1G;
		break;
	case 1:
		*speed = HCLGE_MAC_SPEED_10G;
		break;
	case 2:
		*speed = HCLGE_MAC_SPEED_25G;
		break;
	case 3:
		*speed = HCLGE_MAC_SPEED_40G;
		break;
	case 4:
		*speed = HCLGE_MAC_SPEED_50G;
		break;
	case 5:
		*speed = HCLGE_MAC_SPEED_100G;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}