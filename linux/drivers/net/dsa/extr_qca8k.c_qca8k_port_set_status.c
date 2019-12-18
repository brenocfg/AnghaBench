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
struct qca8k_priv {int dummy; } ;

/* Variables and functions */
 int QCA8K_PORT_STATUS_LINK_AUTO ; 
 int QCA8K_PORT_STATUS_RXMAC ; 
 int QCA8K_PORT_STATUS_TXMAC ; 
 int /*<<< orphan*/  QCA8K_REG_PORT_STATUS (int) ; 
 int /*<<< orphan*/  qca8k_reg_clear (struct qca8k_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qca8k_reg_set (struct qca8k_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qca8k_port_set_status(struct qca8k_priv *priv, int port, int enable)
{
	u32 mask = QCA8K_PORT_STATUS_TXMAC | QCA8K_PORT_STATUS_RXMAC;

	/* Port 0 and 6 have no internal PHY */
	if (port > 0 && port < 6)
		mask |= QCA8K_PORT_STATUS_LINK_AUTO;

	if (enable)
		qca8k_reg_set(priv, QCA8K_REG_PORT_STATUS(port), mask);
	else
		qca8k_reg_clear(priv, QCA8K_REG_PORT_STATUS(port), mask);
}