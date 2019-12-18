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
 int /*<<< orphan*/  BIT (int) ; 
 int QCA8K_CPU_PORT ; 
 int QCA8K_NUM_PORTS ; 
 int /*<<< orphan*/  QCA8K_PORT_LOOKUP_CTRL (int) ; 
 int /*<<< orphan*/  QCA8K_PORT_LOOKUP_MEMBER ; 
 TYPE_1__* dsa_to_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  qca8k_reg_clear (struct qca8k_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qca8k_rmw (struct qca8k_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qca8k_port_bridge_leave(struct dsa_switch *ds, int port, struct net_device *br)
{
	struct qca8k_priv *priv = (struct qca8k_priv *)ds->priv;
	int i;

	for (i = 1; i < QCA8K_NUM_PORTS; i++) {
		if (dsa_to_port(ds, i)->bridge_dev != br)
			continue;
		/* Remove this port to the portvlan mask of the other ports
		 * in the bridge
		 */
		qca8k_reg_clear(priv,
				QCA8K_PORT_LOOKUP_CTRL(i),
				BIT(port));
	}

	/* Set the cpu port to be the only one in the portvlan mask of
	 * this port
	 */
	qca8k_rmw(priv, QCA8K_PORT_LOOKUP_CTRL(port),
		  QCA8K_PORT_LOOKUP_MEMBER, BIT(QCA8K_CPU_PORT));
}