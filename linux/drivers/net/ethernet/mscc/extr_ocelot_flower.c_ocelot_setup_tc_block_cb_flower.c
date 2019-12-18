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
struct ocelot_port_block {TYPE_1__* port; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_CLSFLOWER 129 
#define  TC_SETUP_CLSMATCHALL 128 
 int ocelot_setup_tc_cls_flower (void*,void*) ; 
 int /*<<< orphan*/  tc_cls_can_offload_and_chain0 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int ocelot_setup_tc_block_cb_flower(enum tc_setup_type type,
					   void *type_data, void *cb_priv)
{
	struct ocelot_port_block *port_block = cb_priv;

	if (!tc_cls_can_offload_and_chain0(port_block->port->dev, type_data))
		return -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_CLSFLOWER:
		return ocelot_setup_tc_cls_flower(type_data, cb_priv);
	case TC_SETUP_CLSMATCHALL:
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}