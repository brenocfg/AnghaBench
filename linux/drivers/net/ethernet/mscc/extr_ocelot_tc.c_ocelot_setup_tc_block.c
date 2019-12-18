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
struct TYPE_2__ {int /*<<< orphan*/  block_shared; } ;
struct ocelot_port {TYPE_1__ tc; int /*<<< orphan*/  dev; } ;
struct flow_block_offload {int command; scalar_t__ binder_type; int /*<<< orphan*/  block; int /*<<< orphan*/ * driver_block_list; int /*<<< orphan*/  block_shared; } ;
struct flow_block_cb {int /*<<< orphan*/  driver_list; } ;
typedef  int /*<<< orphan*/  flow_setup_cb_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
#define  FLOW_BLOCK_BIND 129 
 scalar_t__ FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS ; 
 scalar_t__ FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS ; 
#define  FLOW_BLOCK_UNBIND 128 
 int /*<<< orphan*/  IS_ERR (struct flow_block_cb*) ; 
 int PTR_ERR (struct flow_block_cb*) ; 
 int /*<<< orphan*/  flow_block_cb_add (struct flow_block_cb*,struct flow_block_offload*) ; 
 struct flow_block_cb* flow_block_cb_alloc (int /*<<< orphan*/ *,struct ocelot_port*,struct ocelot_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flow_block_cb_free (struct flow_block_cb*) ; 
 int /*<<< orphan*/  flow_block_cb_is_busy (int /*<<< orphan*/ *,struct ocelot_port*,int /*<<< orphan*/ *) ; 
 struct flow_block_cb* flow_block_cb_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ocelot_port*) ; 
 int /*<<< orphan*/  flow_block_cb_remove (struct flow_block_cb*,struct flow_block_offload*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  ocelot_block_cb_list ; 
 int /*<<< orphan*/ * ocelot_setup_tc_block_cb_eg ; 
 int /*<<< orphan*/ * ocelot_setup_tc_block_cb_ig ; 
 int ocelot_setup_tc_block_flower_bind (struct ocelot_port*,struct flow_block_offload*) ; 
 int /*<<< orphan*/  ocelot_setup_tc_block_flower_unbind (struct ocelot_port*,struct flow_block_offload*) ; 

__attribute__((used)) static int ocelot_setup_tc_block(struct ocelot_port *port,
				 struct flow_block_offload *f)
{
	struct flow_block_cb *block_cb;
	flow_setup_cb_t *cb;
	int err;

	netdev_dbg(port->dev, "tc_block command %d, binder_type %d\n",
		   f->command, f->binder_type);

	if (f->binder_type == FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS) {
		cb = ocelot_setup_tc_block_cb_ig;
		port->tc.block_shared = f->block_shared;
	} else if (f->binder_type == FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS) {
		cb = ocelot_setup_tc_block_cb_eg;
	} else {
		return -EOPNOTSUPP;
	}

	f->driver_block_list = &ocelot_block_cb_list;

	switch (f->command) {
	case FLOW_BLOCK_BIND:
		if (flow_block_cb_is_busy(cb, port, &ocelot_block_cb_list))
			return -EBUSY;

		block_cb = flow_block_cb_alloc(cb, port, port, NULL);
		if (IS_ERR(block_cb))
			return PTR_ERR(block_cb);

		err = ocelot_setup_tc_block_flower_bind(port, f);
		if (err < 0) {
			flow_block_cb_free(block_cb);
			return err;
		}
		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, f->driver_block_list);
		return 0;
	case FLOW_BLOCK_UNBIND:
		block_cb = flow_block_cb_lookup(f->block, cb, port);
		if (!block_cb)
			return -ENOENT;

		ocelot_setup_tc_block_flower_unbind(port, f);
		flow_block_cb_remove(block_cb, f);
		list_del(&block_cb->driver_list);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}