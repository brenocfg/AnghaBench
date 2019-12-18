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
struct sja1105_private {int dummy; } ;
struct phylink_link_state {int /*<<< orphan*/  speed; int /*<<< orphan*/  interface; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct sja1105_private* priv; } ;

/* Variables and functions */
 unsigned int MLO_AN_INBAND ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sja1105_adjust_port_config (struct sja1105_private*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sja1105_phy_mode_mismatch (struct sja1105_private*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sja1105_mac_config(struct dsa_switch *ds, int port,
			       unsigned int link_an_mode,
			       const struct phylink_link_state *state)
{
	struct sja1105_private *priv = ds->priv;

	if (sja1105_phy_mode_mismatch(priv, port, state->interface))
		return;

	if (link_an_mode == MLO_AN_INBAND) {
		dev_err(ds->dev, "In-band AN not supported!\n");
		return;
	}

	sja1105_adjust_port_config(priv, port, state->speed);
}