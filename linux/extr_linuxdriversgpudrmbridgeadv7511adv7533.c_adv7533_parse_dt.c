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
typedef  int u32 ;
struct device_node {int dummy; } ;
struct adv7511 {int num_dsi_lanes; int use_timing_gen; int rgb; int embedded_sync; int /*<<< orphan*/  host_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  of_graph_get_remote_node (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 

int adv7533_parse_dt(struct device_node *np, struct adv7511 *adv)
{
	u32 num_lanes;

	of_property_read_u32(np, "adi,dsi-lanes", &num_lanes);

	if (num_lanes < 1 || num_lanes > 4)
		return -EINVAL;

	adv->num_dsi_lanes = num_lanes;

	adv->host_node = of_graph_get_remote_node(np, 0, 0);
	if (!adv->host_node)
		return -ENODEV;

	of_node_put(adv->host_node);

	adv->use_timing_gen = !of_property_read_bool(np,
						"adi,disable-timing-generator");

	/* TODO: Check if these need to be parsed by DT or not */
	adv->rgb = true;
	adv->embedded_sync = false;

	return 0;
}