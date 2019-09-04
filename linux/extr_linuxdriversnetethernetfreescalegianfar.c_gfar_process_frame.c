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
typedef  int /*<<< orphan*/  u64 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct rxfcb {int /*<<< orphan*/  vlctl; int /*<<< orphan*/  flags; } ;
struct net_device {int features; } ;
struct gfar_private {scalar_t__ padding; scalar_t__ hwts_rx_en; scalar_t__ uses_rxfcb; } ;

/* Variables and functions */
 scalar_t__ ETH_FCS_LEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 scalar_t__ GMAC_FCB_LEN ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXCSUM ; 
 int RXFCB_VLN ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfar_rx_checksum (struct sk_buff*,struct rxfcb*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pskb_trim (struct sk_buff*,scalar_t__) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void gfar_process_frame(struct net_device *ndev, struct sk_buff *skb)
{
	struct gfar_private *priv = netdev_priv(ndev);
	struct rxfcb *fcb = NULL;

	/* fcb is at the beginning if exists */
	fcb = (struct rxfcb *)skb->data;

	/* Remove the FCB from the skb
	 * Remove the padded bytes, if there are any
	 */
	if (priv->uses_rxfcb)
		skb_pull(skb, GMAC_FCB_LEN);

	/* Get receive timestamp from the skb */
	if (priv->hwts_rx_en) {
		struct skb_shared_hwtstamps *shhwtstamps = skb_hwtstamps(skb);
		u64 *ns = (u64 *) skb->data;

		memset(shhwtstamps, 0, sizeof(*shhwtstamps));
		shhwtstamps->hwtstamp = ns_to_ktime(be64_to_cpu(*ns));
	}

	if (priv->padding)
		skb_pull(skb, priv->padding);

	/* Trim off the FCS */
	pskb_trim(skb, skb->len - ETH_FCS_LEN);

	if (ndev->features & NETIF_F_RXCSUM)
		gfar_rx_checksum(skb, fcb);

	/* There's need to check for NETIF_F_HW_VLAN_CTAG_RX here.
	 * Even if vlan rx accel is disabled, on some chips
	 * RXFCB_VLN is pseudo randomly set.
	 */
	if (ndev->features & NETIF_F_HW_VLAN_CTAG_RX &&
	    be16_to_cpu(fcb->flags) & RXFCB_VLN)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       be16_to_cpu(fcb->vlctl));
}