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
struct TYPE_2__ {int /*<<< orphan*/  skb_rxtstamp_queue; int /*<<< orphan*/  rxtstamp_work; } ;
struct sja1105_private {int /*<<< orphan*/  static_config; TYPE_1__ tagger_data; } ;
struct dsa_switch {struct sja1105_private* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sja1105_ptp_clock_unregister (struct sja1105_private*) ; 
 int /*<<< orphan*/  sja1105_static_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sja1105_tas_teardown (struct dsa_switch*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sja1105_teardown(struct dsa_switch *ds)
{
	struct sja1105_private *priv = ds->priv;

	sja1105_tas_teardown(ds);
	cancel_work_sync(&priv->tagger_data.rxtstamp_work);
	skb_queue_purge(&priv->tagger_data.skb_rxtstamp_queue);
	sja1105_ptp_clock_unregister(priv);
	sja1105_static_config_free(&priv->static_config);
}