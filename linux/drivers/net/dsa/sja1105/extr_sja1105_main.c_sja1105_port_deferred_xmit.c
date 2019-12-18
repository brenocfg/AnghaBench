#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; int /*<<< orphan*/  member_0; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* read ) (TYPE_1__*) ;} ;
struct sja1105_private {int /*<<< orphan*/  mgmt_lock; int /*<<< orphan*/  ptp_lock; int /*<<< orphan*/  tstamp_tc; TYPE_1__ tstamp_cc; struct sja1105_port* ports; } ;
struct sja1105_port {int mgmt_slot; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct sja1105_private* priv; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_6__ {struct sk_buff* clone; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_flags; } ;

/* Variables and functions */
 TYPE_3__* DSA_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  SKBTX_IN_PROGRESS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sja1105_mgmt_xmit (struct dsa_switch*,int,int,struct sk_buff*,int) ; 
 int sja1105_ptpegr_ts_poll (struct sja1105_private*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sja1105_tstamp_reconstruct (struct sja1105_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_complete_tx_timestamp (struct sk_buff*,struct skb_shared_hwtstamps*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  timecounter_cyc2time (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t sja1105_port_deferred_xmit(struct dsa_switch *ds, int port,
					      struct sk_buff *skb)
{
	struct sja1105_private *priv = ds->priv;
	struct sja1105_port *sp = &priv->ports[port];
	struct skb_shared_hwtstamps shwt = {0};
	int slot = sp->mgmt_slot;
	struct sk_buff *clone;
	u64 now, ts;
	int rc;

	/* The tragic fact about the switch having 4x2 slots for installing
	 * management routes is that all of them except one are actually
	 * useless.
	 * If 2 slots are simultaneously configured for two BPDUs sent to the
	 * same (multicast) DMAC but on different egress ports, the switch
	 * would confuse them and redirect first frame it receives on the CPU
	 * port towards the port configured on the numerically first slot
	 * (therefore wrong port), then second received frame on second slot
	 * (also wrong port).
	 * So for all practical purposes, there needs to be a lock that
	 * prevents that from happening. The slot used here is utterly useless
	 * (could have simply been 0 just as fine), but we are doing it
	 * nonetheless, in case a smarter idea ever comes up in the future.
	 */
	mutex_lock(&priv->mgmt_lock);

	/* The clone, if there, was made by dsa_skb_tx_timestamp */
	clone = DSA_SKB_CB(skb)->clone;

	sja1105_mgmt_xmit(ds, port, slot, skb, !!clone);

	if (!clone)
		goto out;

	skb_shinfo(clone)->tx_flags |= SKBTX_IN_PROGRESS;

	mutex_lock(&priv->ptp_lock);

	now = priv->tstamp_cc.read(&priv->tstamp_cc);

	rc = sja1105_ptpegr_ts_poll(priv, slot, &ts);
	if (rc < 0) {
		dev_err(ds->dev, "xmit: timed out polling for tstamp\n");
		kfree_skb(clone);
		goto out_unlock_ptp;
	}

	ts = sja1105_tstamp_reconstruct(priv, now, ts);
	ts = timecounter_cyc2time(&priv->tstamp_tc, ts);

	shwt.hwtstamp = ns_to_ktime(ts);
	skb_complete_tx_timestamp(clone, &shwt);

out_unlock_ptp:
	mutex_unlock(&priv->ptp_lock);
out:
	mutex_unlock(&priv->mgmt_lock);
	return NETDEV_TX_OK;
}