#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sci_port_configuration_agent {int /*<<< orphan*/  timer; int /*<<< orphan*/  link_down_handler; int /*<<< orphan*/  link_up_handler; } ;
struct TYPE_3__ {int mode_type; } ;
struct TYPE_4__ {TYPE_1__ controller; } ;
struct isci_host {TYPE_2__ oem_parameters; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;
typedef  enum sci_port_configuration_mode { ____Placeholder_sci_port_configuration_mode } sci_port_configuration_mode ;

/* Variables and functions */
 int SCIC_PORT_MANUAL_CONFIGURATION_MODE ; 
 int /*<<< orphan*/  apc_agent_timeout ; 
 int /*<<< orphan*/  mpc_agent_timeout ; 
 int /*<<< orphan*/  sci_apc_agent_link_down ; 
 int /*<<< orphan*/  sci_apc_agent_link_up ; 
 int sci_apc_agent_validate_phy_configuration (struct isci_host*,struct sci_port_configuration_agent*) ; 
 int /*<<< orphan*/  sci_init_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sci_mpc_agent_link_down ; 
 int /*<<< orphan*/  sci_mpc_agent_link_up ; 
 int sci_mpc_agent_validate_phy_configuration (struct isci_host*,struct sci_port_configuration_agent*) ; 

enum sci_status sci_port_configuration_agent_initialize(
	struct isci_host *ihost,
	struct sci_port_configuration_agent *port_agent)
{
	enum sci_status status;
	enum sci_port_configuration_mode mode;

	mode = ihost->oem_parameters.controller.mode_type;

	if (mode == SCIC_PORT_MANUAL_CONFIGURATION_MODE) {
		status = sci_mpc_agent_validate_phy_configuration(
				ihost, port_agent);

		port_agent->link_up_handler = sci_mpc_agent_link_up;
		port_agent->link_down_handler = sci_mpc_agent_link_down;

		sci_init_timer(&port_agent->timer, mpc_agent_timeout);
	} else {
		status = sci_apc_agent_validate_phy_configuration(
				ihost, port_agent);

		port_agent->link_up_handler = sci_apc_agent_link_up;
		port_agent->link_down_handler = sci_apc_agent_link_down;

		sci_init_timer(&port_agent->timer, apc_agent_timeout);
	}

	return status;
}