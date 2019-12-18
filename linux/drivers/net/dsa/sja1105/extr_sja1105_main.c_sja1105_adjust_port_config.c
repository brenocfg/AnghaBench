#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sja1105_xmii_params_entry {scalar_t__* xmii_mode; int /*<<< orphan*/  speed; } ;
struct TYPE_6__ {TYPE_2__* tables; } ;
struct sja1105_private {TYPE_3__ static_config; TYPE_1__* ds; } ;
struct sja1105_mac_config_entry {scalar_t__* xmii_mode; int /*<<< orphan*/  speed; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  sja1105_speed_t ;
typedef  scalar_t__ sja1105_phy_interface_t ;
struct TYPE_5__ {struct sja1105_xmii_params_entry* entries; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 size_t BLK_IDX_MAC_CONFIG ; 
 size_t BLK_IDX_XMII_PARAMS ; 
 int EINVAL ; 
 int /*<<< orphan*/  SJA1105_SPEED_1000MBPS ; 
 int /*<<< orphan*/  SJA1105_SPEED_100MBPS ; 
 int /*<<< orphan*/  SJA1105_SPEED_10MBPS ; 
 int /*<<< orphan*/  SJA1105_SPEED_AUTO ; 
#define  SPEED_10 131 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_UNKNOWN 128 
 scalar_t__ XMII_MODE_RGMII ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int sja1105_clocking_setup_port (struct sja1105_private*,int) ; 
 int sja1105_dynamic_config_write (struct sja1105_private*,size_t,int,struct sja1105_xmii_params_entry*,int) ; 

__attribute__((used)) static int sja1105_adjust_port_config(struct sja1105_private *priv, int port,
				      int speed_mbps)
{
	struct sja1105_xmii_params_entry *mii;
	struct sja1105_mac_config_entry *mac;
	struct device *dev = priv->ds->dev;
	sja1105_phy_interface_t phy_mode;
	sja1105_speed_t speed;
	int rc;

	/* On P/Q/R/S, one can read from the device via the MAC reconfiguration
	 * tables. On E/T, MAC reconfig tables are not readable, only writable.
	 * We have to *know* what the MAC looks like.  For the sake of keeping
	 * the code common, we'll use the static configuration tables as a
	 * reasonable approximation for both E/T and P/Q/R/S.
	 */
	mac = priv->static_config.tables[BLK_IDX_MAC_CONFIG].entries;
	mii = priv->static_config.tables[BLK_IDX_XMII_PARAMS].entries;

	switch (speed_mbps) {
	case SPEED_UNKNOWN:
		/* PHYLINK called sja1105_mac_config() to inform us about
		 * the state->interface, but AN has not completed and the
		 * speed is not yet valid. UM10944.pdf says that setting
		 * SJA1105_SPEED_AUTO at runtime disables the port, so that is
		 * ok for power consumption in case AN will never complete -
		 * otherwise PHYLINK should come back with a new update.
		 */
		speed = SJA1105_SPEED_AUTO;
		break;
	case SPEED_10:
		speed = SJA1105_SPEED_10MBPS;
		break;
	case SPEED_100:
		speed = SJA1105_SPEED_100MBPS;
		break;
	case SPEED_1000:
		speed = SJA1105_SPEED_1000MBPS;
		break;
	default:
		dev_err(dev, "Invalid speed %iMbps\n", speed_mbps);
		return -EINVAL;
	}

	/* Overwrite SJA1105_SPEED_AUTO from the static MAC configuration
	 * table, since this will be used for the clocking setup, and we no
	 * longer need to store it in the static config (already told hardware
	 * we want auto during upload phase).
	 */
	mac[port].speed = speed;

	/* Write to the dynamic reconfiguration tables */
	rc = sja1105_dynamic_config_write(priv, BLK_IDX_MAC_CONFIG, port,
					  &mac[port], true);
	if (rc < 0) {
		dev_err(dev, "Failed to write MAC config: %d\n", rc);
		return rc;
	}

	/* Reconfigure the PLLs for the RGMII interfaces (required 125 MHz at
	 * gigabit, 25 MHz at 100 Mbps and 2.5 MHz at 10 Mbps). For MII and
	 * RMII no change of the clock setup is required. Actually, changing
	 * the clock setup does interrupt the clock signal for a certain time
	 * which causes trouble for all PHYs relying on this signal.
	 */
	phy_mode = mii->xmii_mode[port];
	if (phy_mode != XMII_MODE_RGMII)
		return 0;

	return sja1105_clocking_setup_port(priv, port);
}