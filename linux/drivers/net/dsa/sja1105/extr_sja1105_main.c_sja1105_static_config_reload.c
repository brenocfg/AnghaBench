#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* tables; } ;
struct sja1105_private {TYPE_1__ static_config; } ;
struct sja1105_mac_config_entry {size_t speed; } ;
struct TYPE_4__ {struct sja1105_mac_config_entry* entries; } ;

/* Variables and functions */
 size_t BLK_IDX_MAC_CONFIG ; 
 int SJA1105_NUM_PORTS ; 
 size_t SJA1105_SPEED_AUTO ; 
 int sja1105_adjust_port_config (struct sja1105_private*,int,int) ; 
 int sja1105_clocking_setup (struct sja1105_private*) ; 
 int* sja1105_speed ; 
 int sja1105_static_config_upload (struct sja1105_private*) ; 

int sja1105_static_config_reload(struct sja1105_private *priv)
{
	struct sja1105_mac_config_entry *mac;
	int speed_mbps[SJA1105_NUM_PORTS];
	int rc, i;

	mac = priv->static_config.tables[BLK_IDX_MAC_CONFIG].entries;

	/* Back up the dynamic link speed changed by sja1105_adjust_port_config
	 * in order to temporarily restore it to SJA1105_SPEED_AUTO - which the
	 * switch wants to see in the static config in order to allow us to
	 * change it through the dynamic interface later.
	 */
	for (i = 0; i < SJA1105_NUM_PORTS; i++) {
		speed_mbps[i] = sja1105_speed[mac[i].speed];
		mac[i].speed = SJA1105_SPEED_AUTO;
	}

	/* Reset switch and send updated static configuration */
	rc = sja1105_static_config_upload(priv);
	if (rc < 0)
		goto out;

	/* Configure the CGU (PLLs) for MII and RMII PHYs.
	 * For these interfaces there is no dynamic configuration
	 * needed, since PLLs have same settings at all speeds.
	 */
	rc = sja1105_clocking_setup(priv);
	if (rc < 0)
		goto out;

	for (i = 0; i < SJA1105_NUM_PORTS; i++) {
		rc = sja1105_adjust_port_config(priv, i, speed_mbps[i]);
		if (rc < 0)
			goto out;
	}
out:
	return rc;
}