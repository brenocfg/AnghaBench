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
struct sja1105_table {struct sja1105_l2_lookup_params_entry* entries; } ;
struct TYPE_2__ {struct sja1105_table* tables; } ;
struct sja1105_private {TYPE_1__ static_config; } ;
struct sja1105_l2_lookup_params_entry {unsigned int maxage; } ;
struct dsa_switch {struct sja1105_private* priv; } ;

/* Variables and functions */
 size_t BLK_IDX_L2_LOOKUP_PARAMS ; 
 unsigned int SJA1105_AGEING_TIME_MS (unsigned int) ; 
 int sja1105_static_config_reload (struct sja1105_private*) ; 

__attribute__((used)) static int sja1105_set_ageing_time(struct dsa_switch *ds,
				   unsigned int ageing_time)
{
	struct sja1105_l2_lookup_params_entry *l2_lookup_params;
	struct sja1105_private *priv = ds->priv;
	struct sja1105_table *table;
	unsigned int maxage;

	table = &priv->static_config.tables[BLK_IDX_L2_LOOKUP_PARAMS];
	l2_lookup_params = table->entries;

	maxage = SJA1105_AGEING_TIME_MS(ageing_time);

	if (l2_lookup_params->maxage == maxage)
		return 0;

	l2_lookup_params->maxage = maxage;

	return sja1105_static_config_reload(priv);
}