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
struct sk_buff {int dummy; } ;
struct dpaa2_eth_priv {scalar_t__ tx_tstamp; } ;
struct TYPE_2__ {int tx_flags; } ;

/* Variables and functions */
 unsigned int DPAA2_ETH_SWA_SIZE ; 
 scalar_t__ DPAA2_ETH_TX_HWA_SIZE ; 
 int SKBTX_HW_TSTAMP ; 
 scalar_t__ skb_is_nonlinear (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static inline
unsigned int dpaa2_eth_needed_headroom(struct dpaa2_eth_priv *priv,
				       struct sk_buff *skb)
{
	unsigned int headroom = DPAA2_ETH_SWA_SIZE;

	/* If we don't have an skb (e.g. XDP buffer), we only need space for
	 * the software annotation area
	 */
	if (!skb)
		return headroom;

	/* For non-linear skbs we have no headroom requirement, as we build a
	 * SG frame with a newly allocated SGT buffer
	 */
	if (skb_is_nonlinear(skb))
		return 0;

	/* If we have Tx timestamping, need 128B hardware annotation */
	if (priv->tx_tstamp && skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP)
		headroom += DPAA2_ETH_TX_HWA_SIZE;

	return headroom;
}