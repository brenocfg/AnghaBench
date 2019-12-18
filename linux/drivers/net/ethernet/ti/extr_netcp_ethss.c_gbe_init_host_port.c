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
struct gbe_priv {scalar_t__ ale_ports; int /*<<< orphan*/  ale; int /*<<< orphan*/  host_port; scalar_t__ enable_ale; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_BYPASS ; 
 int /*<<< orphan*/  ALE_NO_PORT_VLAN ; 
 int /*<<< orphan*/  ALE_PORT_STATE ; 
 int ALE_PORT_STATE_FORWARD ; 
 int /*<<< orphan*/  ALE_PORT_UNKNOWN_MCAST_FLOOD ; 
 int /*<<< orphan*/  ALE_PORT_UNKNOWN_REG_MCAST_FLOOD ; 
 int /*<<< orphan*/  ALE_PORT_UNKNOWN_VLAN_MEMBER ; 
 int /*<<< orphan*/  ALE_PORT_UNTAGGED_EGRESS ; 
 int GBE_PORT_MASK (scalar_t__) ; 
 int /*<<< orphan*/  GBE_REG_ADDR (struct gbe_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST_TX_PRI_MAP_DEFAULT ; 
 scalar_t__ IS_SS_ID_NU (struct gbe_priv*) ; 
 scalar_t__ IS_SS_ID_XGBE (struct gbe_priv*) ; 
 int /*<<< orphan*/  NETCP_MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  cpsw_ale_control_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpsw_ale_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_port_regs ; 
 int /*<<< orphan*/  rx_maxlen ; 
 int /*<<< orphan*/  tx_pri_map ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gbe_init_host_port(struct gbe_priv *priv)
{
	int bypass_en = 1;

	/* Host Tx Pri */
	if (IS_SS_ID_NU(priv) || IS_SS_ID_XGBE(priv))
		writel(HOST_TX_PRI_MAP_DEFAULT,
		       GBE_REG_ADDR(priv, host_port_regs, tx_pri_map));

	/* Max length register */
	writel(NETCP_MAX_FRAME_SIZE, GBE_REG_ADDR(priv, host_port_regs,
						  rx_maxlen));

	cpsw_ale_start(priv->ale);

	if (priv->enable_ale)
		bypass_en = 0;

	cpsw_ale_control_set(priv->ale, 0, ALE_BYPASS, bypass_en);

	cpsw_ale_control_set(priv->ale, 0, ALE_NO_PORT_VLAN, 1);

	cpsw_ale_control_set(priv->ale, priv->host_port,
			     ALE_PORT_STATE, ALE_PORT_STATE_FORWARD);

	cpsw_ale_control_set(priv->ale, 0,
			     ALE_PORT_UNKNOWN_VLAN_MEMBER,
			     GBE_PORT_MASK(priv->ale_ports));

	cpsw_ale_control_set(priv->ale, 0,
			     ALE_PORT_UNKNOWN_MCAST_FLOOD,
			     GBE_PORT_MASK(priv->ale_ports - 1));

	cpsw_ale_control_set(priv->ale, 0,
			     ALE_PORT_UNKNOWN_REG_MCAST_FLOOD,
			     GBE_PORT_MASK(priv->ale_ports));

	cpsw_ale_control_set(priv->ale, 0,
			     ALE_PORT_UNTAGGED_EGRESS,
			     GBE_PORT_MASK(priv->ale_ports));
}