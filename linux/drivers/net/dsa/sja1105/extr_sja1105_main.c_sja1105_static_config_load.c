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
struct sja1105_private {TYPE_1__* info; int /*<<< orphan*/  static_config; } ;
struct sja1105_dt_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_id; int /*<<< orphan*/  static_ops; } ;

/* Variables and functions */
 int sja1105_init_avb_params (struct sja1105_private*,int) ; 
 int sja1105_init_general_params (struct sja1105_private*) ; 
 int sja1105_init_l2_forwarding (struct sja1105_private*) ; 
 int sja1105_init_l2_forwarding_params (struct sja1105_private*) ; 
 int sja1105_init_l2_lookup_params (struct sja1105_private*) ; 
 int sja1105_init_l2_policing (struct sja1105_private*) ; 
 int sja1105_init_mac_settings (struct sja1105_private*) ; 
 int sja1105_init_mii_settings (struct sja1105_private*,struct sja1105_dt_port*) ; 
 int sja1105_init_static_fdb (struct sja1105_private*) ; 
 int sja1105_init_static_vlan (struct sja1105_private*) ; 
 int /*<<< orphan*/  sja1105_static_config_free (int /*<<< orphan*/ *) ; 
 int sja1105_static_config_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sja1105_static_config_upload (struct sja1105_private*) ; 

__attribute__((used)) static int sja1105_static_config_load(struct sja1105_private *priv,
				      struct sja1105_dt_port *ports)
{
	int rc;

	sja1105_static_config_free(&priv->static_config);
	rc = sja1105_static_config_init(&priv->static_config,
					priv->info->static_ops,
					priv->info->device_id);
	if (rc)
		return rc;

	/* Build static configuration */
	rc = sja1105_init_mac_settings(priv);
	if (rc < 0)
		return rc;
	rc = sja1105_init_mii_settings(priv, ports);
	if (rc < 0)
		return rc;
	rc = sja1105_init_static_fdb(priv);
	if (rc < 0)
		return rc;
	rc = sja1105_init_static_vlan(priv);
	if (rc < 0)
		return rc;
	rc = sja1105_init_l2_lookup_params(priv);
	if (rc < 0)
		return rc;
	rc = sja1105_init_l2_forwarding(priv);
	if (rc < 0)
		return rc;
	rc = sja1105_init_l2_forwarding_params(priv);
	if (rc < 0)
		return rc;
	rc = sja1105_init_l2_policing(priv);
	if (rc < 0)
		return rc;
	rc = sja1105_init_general_params(priv);
	if (rc < 0)
		return rc;
	rc = sja1105_init_avb_params(priv, false);
	if (rc < 0)
		return rc;

	/* Send initial configuration to hardware via SPI */
	return sja1105_static_config_upload(priv);
}