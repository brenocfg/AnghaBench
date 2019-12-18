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
struct TYPE_2__ {scalar_t__ link_up_handler; } ;
struct isci_host {TYPE_1__ port_agent; } ;

/* Variables and functions */
 scalar_t__ sci_apc_agent_link_up ; 

bool is_port_config_apc(struct isci_host *ihost)
{
	return ihost->port_agent.link_up_handler == sci_apc_agent_link_up;
}