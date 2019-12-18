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
struct sja1105_table {struct sja1105_general_params_entry* entries; } ;
struct TYPE_3__ {int /*<<< orphan*/ * stampable_skb; } ;
struct TYPE_4__ {struct sja1105_table* tables; } ;
struct sja1105_private {TYPE_1__ tagger_data; TYPE_2__ static_config; } ;
struct sja1105_general_params_entry {int send_meta1; int send_meta0; } ;

/* Variables and functions */
 size_t BLK_IDX_GENERAL_PARAMS ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int sja1105_init_avb_params (struct sja1105_private*,int) ; 
 int sja1105_static_config_reload (struct sja1105_private*) ; 

__attribute__((used)) static int sja1105_change_rxtstamping(struct sja1105_private *priv,
				      bool on)
{
	struct sja1105_general_params_entry *general_params;
	struct sja1105_table *table;
	int rc;

	table = &priv->static_config.tables[BLK_IDX_GENERAL_PARAMS];
	general_params = table->entries;
	general_params->send_meta1 = on;
	general_params->send_meta0 = on;

	rc = sja1105_init_avb_params(priv, on);
	if (rc < 0)
		return rc;

	/* Initialize the meta state machine to a known state */
	if (priv->tagger_data.stampable_skb) {
		kfree_skb(priv->tagger_data.stampable_skb);
		priv->tagger_data.stampable_skb = NULL;
	}

	return sja1105_static_config_reload(priv);
}