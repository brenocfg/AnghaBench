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
struct qca8k_priv {TYPE_1__* port_sts; } ;
struct phy_device {int dummy; } ;
struct dsa_switch {scalar_t__ priv; } ;
struct TYPE_2__ {int enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  dsa_is_user_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  phy_support_asym_pause (struct phy_device*) ; 
 int /*<<< orphan*/  qca8k_port_set_status (struct qca8k_priv*,int,int) ; 

__attribute__((used)) static int
qca8k_port_enable(struct dsa_switch *ds, int port,
		  struct phy_device *phy)
{
	struct qca8k_priv *priv = (struct qca8k_priv *)ds->priv;

	if (!dsa_is_user_port(ds, port))
		return 0;

	qca8k_port_set_status(priv, port, 1);
	priv->port_sts[port].enabled = 1;

	phy_support_asym_pause(phy);

	return 0;
}