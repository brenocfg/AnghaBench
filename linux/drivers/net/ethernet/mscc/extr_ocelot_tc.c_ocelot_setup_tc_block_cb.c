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
struct ocelot_port {int /*<<< orphan*/  dev; } ;
typedef  enum tc_setup_type { ____Placeholder_tc_setup_type } tc_setup_type ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  TC_SETUP_CLSFLOWER 129 
#define  TC_SETUP_CLSMATCHALL 128 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int ocelot_setup_tc_cls_matchall (struct ocelot_port*,void*,int) ; 
 int /*<<< orphan*/  tc_cls_can_offload_and_chain0 (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int ocelot_setup_tc_block_cb(enum tc_setup_type type,
				    void *type_data,
				    void *cb_priv, bool ingress)
{
	struct ocelot_port *port = cb_priv;

	if (!tc_cls_can_offload_and_chain0(port->dev, type_data))
		return -EOPNOTSUPP;

	switch (type) {
	case TC_SETUP_CLSMATCHALL:
		netdev_dbg(port->dev, "tc_block_cb: TC_SETUP_CLSMATCHALL %s\n",
			   ingress ? "ingress" : "egress");

		return ocelot_setup_tc_cls_matchall(port, type_data, ingress);
	case TC_SETUP_CLSFLOWER:
		return 0;
	default:
		netdev_dbg(port->dev, "tc_block_cb: type %d %s\n",
			   type,
			   ingress ? "ingress" : "egress");

		return -EOPNOTSUPP;
	}
}