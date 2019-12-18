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
struct qca8k_priv {int dummy; } ;
struct net_device {int dummy; } ;
struct dsa_switch {scalar_t__ priv; } ;
struct TYPE_2__ {struct net_device* bridge_dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int QCA8K_CPU_PORT ; 
 int QCA8K_NUM_PORTS ; 
 int /*<<< orphan*/  QCA8K_PORT_LOOKUP_CTRL (int) ; 
 int /*<<< orphan*/  QCA8K_PORT_LOOKUP_MEMBER ; 
 TYPE_1__* dsa_to_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  qca8k_reg_set (struct qca8k_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qca8k_rmw (struct qca8k_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
qca8k_port_bridge_join(struct dsa_switch *ds, int port, struct net_device *br)
{
	struct qca8k_priv *priv = (struct qca8k_priv *)ds->priv;
	int port_mask = BIT(QCA8K_CPU_PORT);
	int i;

	for (i = 1; i < QCA8K_NUM_PORTS; i++) {
		if (dsa_to_port(ds, i)->bridge_dev != br)
			continue;
		/* Add this port to the portvlan mask of the other ports
		 * in the bridge
		 */
		qca8k_reg_set(priv,
			      QCA8K_PORT_LOOKUP_CTRL(i),
			      BIT(port));
		if (i != port)
			port_mask |= BIT(i);
	}
	/* Add all other ports to this ports portvlan mask */
	qca8k_rmw(priv, QCA8K_PORT_LOOKUP_CTRL(port),
		  QCA8K_PORT_LOOKUP_MEMBER, port_mask);

	return 0;
}