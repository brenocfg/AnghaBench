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
struct sk_buff {int dummy; } ;
struct sja1105_private {struct sja1105_port* ports; } ;
struct sja1105_port {int /*<<< orphan*/  hwts_tx_en; } ;
struct dsa_switch {struct sja1105_private* priv; } ;

/* Variables and functions */

__attribute__((used)) static bool sja1105_port_txtstamp(struct dsa_switch *ds, int port,
				  struct sk_buff *skb, unsigned int type)
{
	struct sja1105_private *priv = ds->priv;
	struct sja1105_port *sp = &priv->ports[port];

	if (!sp->hwts_tx_en)
		return false;

	return true;
}