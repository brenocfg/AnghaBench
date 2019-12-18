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
struct ocelot_port {int dummy; } ;
struct flow_block_offload {int /*<<< orphan*/  block; } ;
struct flow_block_cb {int /*<<< orphan*/  driver_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_block_cb_decref (struct flow_block_cb*) ; 
 struct flow_block_cb* flow_block_cb_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocelot_port*) ; 
 int /*<<< orphan*/  flow_block_cb_remove (struct flow_block_cb*,struct flow_block_offload*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocelot_setup_tc_block_cb_flower ; 

void ocelot_setup_tc_block_flower_unbind(struct ocelot_port *port,
					 struct flow_block_offload *f)
{
	struct flow_block_cb *block_cb;

	block_cb = flow_block_cb_lookup(f->block,
					ocelot_setup_tc_block_cb_flower, port);
	if (!block_cb)
		return;

	if (!flow_block_cb_decref(block_cb)) {
		flow_block_cb_remove(block_cb, f);
		list_del(&block_cb->driver_list);
	}
}