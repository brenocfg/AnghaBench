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
typedef  int u8 ;
struct TYPE_4__ {TYPE_1__* tables; } ;
struct sja1105_private {TYPE_2__ static_config; } ;
struct sja1105_mac_config_entry {int ingress; int egress; int dyn_learn; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct sja1105_private* priv; } ;
struct TYPE_3__ {struct sja1105_mac_config_entry* entries; } ;

/* Variables and functions */
 size_t BLK_IDX_MAC_CONFIG ; 
#define  BR_STATE_BLOCKING 132 
#define  BR_STATE_DISABLED 131 
#define  BR_STATE_FORWARDING 130 
#define  BR_STATE_LEARNING 129 
#define  BR_STATE_LISTENING 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sja1105_dynamic_config_write (struct sja1105_private*,size_t,int,struct sja1105_mac_config_entry*,int) ; 

__attribute__((used)) static void sja1105_bridge_stp_state_set(struct dsa_switch *ds, int port,
					 u8 state)
{
	struct sja1105_private *priv = ds->priv;
	struct sja1105_mac_config_entry *mac;

	mac = priv->static_config.tables[BLK_IDX_MAC_CONFIG].entries;

	switch (state) {
	case BR_STATE_DISABLED:
	case BR_STATE_BLOCKING:
		/* From UM10944 description of DRPDTAG (why put this there?):
		 * "Management traffic flows to the port regardless of the state
		 * of the INGRESS flag". So BPDUs are still be allowed to pass.
		 * At the moment no difference between DISABLED and BLOCKING.
		 */
		mac[port].ingress   = false;
		mac[port].egress    = false;
		mac[port].dyn_learn = false;
		break;
	case BR_STATE_LISTENING:
		mac[port].ingress   = true;
		mac[port].egress    = false;
		mac[port].dyn_learn = false;
		break;
	case BR_STATE_LEARNING:
		mac[port].ingress   = true;
		mac[port].egress    = false;
		mac[port].dyn_learn = true;
		break;
	case BR_STATE_FORWARDING:
		mac[port].ingress   = true;
		mac[port].egress    = true;
		mac[port].dyn_learn = true;
		break;
	default:
		dev_err(ds->dev, "invalid STP state: %d\n", state);
		return;
	}

	sja1105_dynamic_config_write(priv, BLK_IDX_MAC_CONFIG, port,
				     &mac[port], true);
}