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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {TYPE_1__* tables; } ;
struct sja1105_private {TYPE_2__ static_config; } ;
struct sja1105_mac_config_entry {int /*<<< orphan*/  vlanid; } ;
struct TYPE_3__ {struct sja1105_mac_config_entry* entries; } ;

/* Variables and functions */
 size_t BLK_IDX_MAC_CONFIG ; 
 int sja1105_dynamic_config_write (struct sja1105_private*,size_t,int,struct sja1105_mac_config_entry*,int) ; 

__attribute__((used)) static int sja1105_pvid_apply(struct sja1105_private *priv, int port, u16 pvid)
{
	struct sja1105_mac_config_entry *mac;

	mac = priv->static_config.tables[BLK_IDX_MAC_CONFIG].entries;

	mac[port].vlanid = pvid;

	return sja1105_dynamic_config_write(priv, BLK_IDX_MAC_CONFIG, port,
					   &mac[port], true);
}