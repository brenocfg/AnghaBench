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
struct qca8k_priv {int /*<<< orphan*/  dev; } ;
struct phy_device {int speed; scalar_t__ duplex; } ;
struct dsa_switch {struct qca8k_priv* priv; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int QCA8K_PORT_STATUS_DUPLEX ; 
 int QCA8K_PORT_STATUS_RXFLOW ; 
 int QCA8K_PORT_STATUS_SPEED_10 ; 
 int QCA8K_PORT_STATUS_SPEED_100 ; 
 int QCA8K_PORT_STATUS_SPEED_1000 ; 
 int QCA8K_PORT_STATUS_TXFLOW ; 
 int /*<<< orphan*/  QCA8K_REG_PORT_STATUS (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ dsa_is_cpu_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  phy_is_pseudo_fixed_link (struct phy_device*) ; 
 int /*<<< orphan*/  qca8k_port_set_status (struct qca8k_priv*,int,int) ; 
 int /*<<< orphan*/  qca8k_write (struct qca8k_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qca8k_adjust_link(struct dsa_switch *ds, int port, struct phy_device *phy)
{
	struct qca8k_priv *priv = ds->priv;
	u32 reg;

	/* Force fixed-link setting for CPU port, skip others. */
	if (!phy_is_pseudo_fixed_link(phy))
		return;

	/* Set port speed */
	switch (phy->speed) {
	case 10:
		reg = QCA8K_PORT_STATUS_SPEED_10;
		break;
	case 100:
		reg = QCA8K_PORT_STATUS_SPEED_100;
		break;
	case 1000:
		reg = QCA8K_PORT_STATUS_SPEED_1000;
		break;
	default:
		dev_dbg(priv->dev, "port%d link speed %dMbps not supported.\n",
			port, phy->speed);
		return;
	}

	/* Set duplex mode */
	if (phy->duplex == DUPLEX_FULL)
		reg |= QCA8K_PORT_STATUS_DUPLEX;

	/* Force flow control */
	if (dsa_is_cpu_port(ds, port))
		reg |= QCA8K_PORT_STATUS_RXFLOW | QCA8K_PORT_STATUS_TXFLOW;

	/* Force link down before changing MAC options */
	qca8k_port_set_status(priv, port, 0);
	qca8k_write(priv, QCA8K_REG_PORT_STATUS(port), reg);
	qca8k_port_set_status(priv, port, 1);
}