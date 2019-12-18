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
typedef  int /*<<< orphan*/  u32 ;
struct phy_device {int speed; scalar_t__ duplex; scalar_t__ link; } ;
struct cpsw_slave {int /*<<< orphan*/  mac_control; int /*<<< orphan*/  mac_sl; struct phy_device* phy; int /*<<< orphan*/  slave_num; } ;
struct cpsw_priv {scalar_t__ shp_cfg_speed; int /*<<< orphan*/  dev; scalar_t__ tx_pause; scalar_t__ rx_pause; struct cpsw_common* cpsw; } ;
struct cpsw_common {int /*<<< orphan*/  ale; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_PORT_STATE ; 
 int /*<<< orphan*/  ALE_PORT_STATE_DISABLE ; 
 int /*<<< orphan*/  ALE_PORT_STATE_FORWARD ; 
 int /*<<< orphan*/  CPSW_SL_CTL_EXT_EN ; 
 int /*<<< orphan*/  CPSW_SL_CTL_FULLDUPLEX ; 
 int /*<<< orphan*/  CPSW_SL_CTL_GIG ; 
 int /*<<< orphan*/  CPSW_SL_CTL_GMII_EN ; 
 int /*<<< orphan*/  CPSW_SL_CTL_IFCTL_A ; 
 int /*<<< orphan*/  CPSW_SL_CTL_RX_FLOW_EN ; 
 int /*<<< orphan*/  CPSW_SL_CTL_TX_FLOW_EN ; 
 int /*<<< orphan*/  cpsw_ale_control_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_get_slave_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_shp_is_off (struct cpsw_priv*) ; 
 int /*<<< orphan*/  cpsw_sl_ctl_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_sl_ctl_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_sl_wait_for_idle (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ phy_interface_is_rgmii (struct phy_device*) ; 
 int /*<<< orphan*/  phy_print_status (struct phy_device*) ; 

__attribute__((used)) static void _cpsw_adjust_link(struct cpsw_slave *slave,
			      struct cpsw_priv *priv, bool *link)
{
	struct phy_device	*phy = slave->phy;
	u32			mac_control = 0;
	u32			slave_port;
	struct cpsw_common *cpsw = priv->cpsw;

	if (!phy)
		return;

	slave_port = cpsw_get_slave_port(slave->slave_num);

	if (phy->link) {
		mac_control = CPSW_SL_CTL_GMII_EN;

		if (phy->speed == 1000)
			mac_control |= CPSW_SL_CTL_GIG;
		if (phy->duplex)
			mac_control |= CPSW_SL_CTL_FULLDUPLEX;

		/* set speed_in input in case RMII mode is used in 100Mbps */
		if (phy->speed == 100)
			mac_control |= CPSW_SL_CTL_IFCTL_A;
		/* in band mode only works in 10Mbps RGMII mode */
		else if ((phy->speed == 10) && phy_interface_is_rgmii(phy))
			mac_control |= CPSW_SL_CTL_EXT_EN; /* In Band mode */

		if (priv->rx_pause)
			mac_control |= CPSW_SL_CTL_RX_FLOW_EN;

		if (priv->tx_pause)
			mac_control |= CPSW_SL_CTL_TX_FLOW_EN;

		if (mac_control != slave->mac_control)
			cpsw_sl_ctl_set(slave->mac_sl, mac_control);

		/* enable forwarding */
		cpsw_ale_control_set(cpsw->ale, slave_port,
				     ALE_PORT_STATE, ALE_PORT_STATE_FORWARD);

		*link = true;

		if (priv->shp_cfg_speed &&
		    priv->shp_cfg_speed != slave->phy->speed &&
		    !cpsw_shp_is_off(priv))
			dev_warn(priv->dev,
				 "Speed was changed, CBS shaper speeds are changed!");
	} else {
		mac_control = 0;
		/* disable forwarding */
		cpsw_ale_control_set(cpsw->ale, slave_port,
				     ALE_PORT_STATE, ALE_PORT_STATE_DISABLE);

		cpsw_sl_wait_for_idle(slave->mac_sl, 100);

		cpsw_sl_ctl_reset(slave->mac_sl);
	}

	if (mac_control != slave->mac_control)
		phy_print_status(phy);

	slave->mac_control = mac_control;
}