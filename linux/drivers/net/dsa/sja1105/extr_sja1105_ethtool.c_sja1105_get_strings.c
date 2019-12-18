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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sja1105_private {TYPE_1__* info; } ;
struct dsa_switch {struct sja1105_private* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  device_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 128 
 int /*<<< orphan*/  SJA1105E_DEVICE_ID ; 
 int /*<<< orphan*/  SJA1105T_DEVICE_ID ; 
 int /*<<< orphan*/ * sja1105_port_stats ; 
 int /*<<< orphan*/ * sja1105pqrs_extra_port_stats ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sja1105_get_strings(struct dsa_switch *ds, int port,
			 u32 stringset, u8 *data)
{
	struct sja1105_private *priv = ds->priv;
	u8 *p = data;
	int i;

	switch (stringset) {
	case ETH_SS_STATS:
		for (i = 0; i < ARRAY_SIZE(sja1105_port_stats); i++) {
			strlcpy(p, sja1105_port_stats[i], ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}
		if (priv->info->device_id == SJA1105E_DEVICE_ID ||
		    priv->info->device_id == SJA1105T_DEVICE_ID)
			return;
		for (i = 0; i < ARRAY_SIZE(sja1105pqrs_extra_port_stats); i++) {
			strlcpy(p, sja1105pqrs_extra_port_stats[i],
				ETH_GSTRING_LEN);
			p += ETH_GSTRING_LEN;
		}
		break;
	}
}