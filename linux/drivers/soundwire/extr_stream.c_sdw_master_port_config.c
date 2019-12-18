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
struct sdw_port_runtime {int /*<<< orphan*/  port_node; } ;
struct sdw_port_config {int dummy; } ;
struct sdw_master_runtime {int /*<<< orphan*/  port_list; } ;
struct sdw_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct sdw_port_runtime* sdw_port_alloc (int /*<<< orphan*/ ,struct sdw_port_config*,int) ; 

__attribute__((used)) static int sdw_master_port_config(struct sdw_bus *bus,
				  struct sdw_master_runtime *m_rt,
				  struct sdw_port_config *port_config,
				  unsigned int num_ports)
{
	struct sdw_port_runtime *p_rt;
	int i;

	/* Iterate for number of ports to perform initialization */
	for (i = 0; i < num_ports; i++) {
		p_rt = sdw_port_alloc(bus->dev, port_config, i);
		if (!p_rt)
			return -ENOMEM;

		/*
		 * TODO: Check port capabilities for requested
		 * configuration (audio mode support)
		 */

		list_add_tail(&p_rt->port_node, &m_rt->port_list);
	}

	return 0;
}