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
struct kernel_ipmi_msg {scalar_t__ netfn; scalar_t__ cmd; } ;

/* Variables and functions */
 scalar_t__ IPMI_COLD_RESET_CMD ; 
 scalar_t__ IPMI_NETFN_APP_REQUEST ; 
 scalar_t__ IPMI_NETFN_FIRMWARE_REQUEST ; 
 scalar_t__ IPMI_WARM_RESET_CMD ; 

__attribute__((used)) static bool is_maintenance_mode_cmd(struct kernel_ipmi_msg *msg)
{
	return (((msg->netfn == IPMI_NETFN_APP_REQUEST)
		 && ((msg->cmd == IPMI_COLD_RESET_CMD)
		     || (msg->cmd == IPMI_WARM_RESET_CMD)))
		|| (msg->netfn == IPMI_NETFN_FIRMWARE_REQUEST));
}