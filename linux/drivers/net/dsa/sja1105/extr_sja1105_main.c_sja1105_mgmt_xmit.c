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
struct sk_buff {int dummy; } ;
struct sja1105_private {TYPE_2__* ds; } ;
struct sja1105_mgmt_entry {int enfport; int takets; scalar_t__ tsreg; int /*<<< orphan*/  destports; int /*<<< orphan*/  macaddr; int /*<<< orphan*/  member_0; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; } ;
struct dsa_switch {TYPE_1__* ports; struct sja1105_private* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  BLK_IDX_MGMT_ROUTE ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dsa_enqueue_skb (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ether_addr_to_u64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int sja1105_dynamic_config_read (struct sja1105_private*,int /*<<< orphan*/ ,int,struct sja1105_mgmt_entry*) ; 
 int sja1105_dynamic_config_write (struct sja1105_private*,int /*<<< orphan*/ ,int,struct sja1105_mgmt_entry*,int) ; 

__attribute__((used)) static int sja1105_mgmt_xmit(struct dsa_switch *ds, int port, int slot,
			     struct sk_buff *skb, bool takets)
{
	struct sja1105_mgmt_entry mgmt_route = {0};
	struct sja1105_private *priv = ds->priv;
	struct ethhdr *hdr;
	int timeout = 10;
	int rc;

	hdr = eth_hdr(skb);

	mgmt_route.macaddr = ether_addr_to_u64(hdr->h_dest);
	mgmt_route.destports = BIT(port);
	mgmt_route.enfport = 1;
	mgmt_route.tsreg = 0;
	mgmt_route.takets = takets;

	rc = sja1105_dynamic_config_write(priv, BLK_IDX_MGMT_ROUTE,
					  slot, &mgmt_route, true);
	if (rc < 0) {
		kfree_skb(skb);
		return rc;
	}

	/* Transfer skb to the host port. */
	dsa_enqueue_skb(skb, ds->ports[port].slave);

	/* Wait until the switch has processed the frame */
	do {
		rc = sja1105_dynamic_config_read(priv, BLK_IDX_MGMT_ROUTE,
						 slot, &mgmt_route);
		if (rc < 0) {
			dev_err_ratelimited(priv->ds->dev,
					    "failed to poll for mgmt route\n");
			continue;
		}

		/* UM10944: The ENFPORT flag of the respective entry is
		 * cleared when a match is found. The host can use this
		 * flag as an acknowledgment.
		 */
		cpu_relax();
	} while (mgmt_route.enfport && --timeout);

	if (!timeout) {
		/* Clean up the management route so that a follow-up
		 * frame may not match on it by mistake.
		 * This is only hardware supported on P/Q/R/S - on E/T it is
		 * a no-op and we are silently discarding the -EOPNOTSUPP.
		 */
		sja1105_dynamic_config_write(priv, BLK_IDX_MGMT_ROUTE,
					     slot, &mgmt_route, false);
		dev_err_ratelimited(priv->ds->dev, "xmit timed out\n");
	}

	return NETDEV_TX_OK;
}