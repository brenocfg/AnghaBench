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
struct sdw_port_runtime {int /*<<< orphan*/  port_params; int /*<<< orphan*/  transport_params; } ;
struct TYPE_4__ {int /*<<< orphan*/  next_bank; } ;
struct sdw_bus {TYPE_2__ params; TYPE_1__* port_ops; } ;
struct TYPE_3__ {int (* dpn_set_port_transport_params ) (struct sdw_bus*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int (* dpn_set_port_params ) (struct sdw_bus*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct sdw_bus*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub2 (struct sdw_bus*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdw_program_master_port_params(struct sdw_bus *bus,
					  struct sdw_port_runtime *p_rt)
{
	int ret;

	/*
	 * we need to set transport and port parameters for the port.
	 * Transport parameters refers to the sample interval, offsets and
	 * hstart/stop etc of the data. Port parameters refers to word
	 * length, flow mode etc of the port
	 */
	ret = bus->port_ops->dpn_set_port_transport_params(bus,
					&p_rt->transport_params,
					bus->params.next_bank);
	if (ret < 0)
		return ret;

	return bus->port_ops->dpn_set_port_params(bus,
						  &p_rt->port_params,
						  bus->params.next_bank);
}