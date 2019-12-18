#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cht_int33fe_data {TYPE_1__* dp; } ;
struct TYPE_5__ {int /*<<< orphan*/ * node; } ;
struct TYPE_4__ {int /*<<< orphan*/ * secondary; } ;

/* Variables and functions */
 int /*<<< orphan*/  fwnode_handle_put (TYPE_1__*) ; 
 TYPE_2__ mux_ref ; 
 int /*<<< orphan*/  nodes ; 
 TYPE_1__* software_node_fwnode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  software_node_unregister_nodes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cht_int33fe_remove_nodes(struct cht_int33fe_data *data)
{
	software_node_unregister_nodes(nodes);

	if (mux_ref.node) {
		fwnode_handle_put(software_node_fwnode(mux_ref.node));
		mux_ref.node = NULL;
	}

	if (data->dp) {
		data->dp->secondary = NULL;
		fwnode_handle_put(data->dp);
		data->dp = NULL;
	}
}