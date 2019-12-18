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
 int NONE_CONNECTION_TYPE ; 
 int RAMROD_CMD_ID_ETH_CLASSIFICATION_RULES ; 
 int RAMROD_CMD_ID_ETH_FILTER_RULES ; 
 int RAMROD_CMD_ID_ETH_FORWARD_SETUP ; 
 int RAMROD_CMD_ID_ETH_MULTICAST_RULES ; 
 int RAMROD_CMD_ID_ETH_RSS_UPDATE ; 
 int RAMROD_CMD_ID_ETH_SET_MAC ; 

__attribute__((used)) static bool bnx2x_is_contextless_ramrod(int cmd, int cmd_type)
{
	if ((cmd_type == NONE_CONNECTION_TYPE) ||
	    (cmd == RAMROD_CMD_ID_ETH_FORWARD_SETUP) ||
	    (cmd == RAMROD_CMD_ID_ETH_CLASSIFICATION_RULES) ||
	    (cmd == RAMROD_CMD_ID_ETH_FILTER_RULES) ||
	    (cmd == RAMROD_CMD_ID_ETH_MULTICAST_RULES) ||
	    (cmd == RAMROD_CMD_ID_ETH_SET_MAC) ||
	    (cmd == RAMROD_CMD_ID_ETH_RSS_UPDATE))
		return true;
	else
		return false;
}