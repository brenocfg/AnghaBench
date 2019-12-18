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
struct sdw_slave_runtime {int /*<<< orphan*/  port_list; } ;
struct sdw_slave {int /*<<< orphan*/  dev; } ;
struct sdw_port_runtime {int /*<<< orphan*/  port_node; } ;
struct sdw_port_config {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kfree (struct sdw_port_runtime*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sdw_is_valid_port_range (int /*<<< orphan*/ *,struct sdw_port_runtime*) ; 
 struct sdw_port_runtime* sdw_port_alloc (int /*<<< orphan*/ *,struct sdw_port_config*,int) ; 

__attribute__((used)) static int sdw_slave_port_config(struct sdw_slave *slave,
				 struct sdw_slave_runtime *s_rt,
				 struct sdw_port_config *port_config,
				 unsigned int num_config)
{
	struct sdw_port_runtime *p_rt;
	int i, ret;

	/* Iterate for number of ports to perform initialization */
	for (i = 0; i < num_config; i++) {
		p_rt = sdw_port_alloc(&slave->dev, port_config, i);
		if (!p_rt)
			return -ENOMEM;

		/*
		 * TODO: Check valid port range as defined by DisCo/
		 * slave
		 */
		ret = sdw_is_valid_port_range(&slave->dev, p_rt);
		if (ret < 0) {
			kfree(p_rt);
			return ret;
		}

		/*
		 * TODO: Check port capabilities for requested
		 * configuration (audio mode support)
		 */

		list_add_tail(&p_rt->port_node, &s_rt->port_list);
	}

	return 0;
}