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
struct sk_buff {int /*<<< orphan*/  csum; scalar_t__ ip_summed; } ;
struct TYPE_4__ {int flags; } ;
struct nfp_net_rx_desc {TYPE_2__ rxd; } ;
struct nfp_net_r_vector {int /*<<< orphan*/  rx_sync; int /*<<< orphan*/  hw_csum_rx_inner_ok; int /*<<< orphan*/  hw_csum_rx_ok; int /*<<< orphan*/  hw_csum_rx_error; int /*<<< orphan*/  hw_csum_rx_complete; } ;
struct nfp_net_dp {TYPE_1__* netdev; } ;
struct nfp_meta_parsed {int /*<<< orphan*/  csum; scalar_t__ csum_type; } ;
struct TYPE_3__ {int features; } ;

/* Variables and functions */
 int NETIF_F_RXCSUM ; 
 int PCIE_DESC_RX_I_TCP_CSUM_OK ; 
 int PCIE_DESC_RX_I_UDP_CSUM_OK ; 
 int PCIE_DESC_RX_TCP_CSUM_OK ; 
 int PCIE_DESC_RX_UDP_CSUM_OK ; 
 int /*<<< orphan*/  __skb_incr_checksum_unnecessary (struct sk_buff*) ; 
 int /*<<< orphan*/  le16_to_cpu (int) ; 
 scalar_t__ nfp_net_rx_csum_has_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_net_rx_csum(struct nfp_net_dp *dp,
			    struct nfp_net_r_vector *r_vec,
			    struct nfp_net_rx_desc *rxd,
			    struct nfp_meta_parsed *meta, struct sk_buff *skb)
{
	skb_checksum_none_assert(skb);

	if (!(dp->netdev->features & NETIF_F_RXCSUM))
		return;

	if (meta->csum_type) {
		skb->ip_summed = meta->csum_type;
		skb->csum = meta->csum;
		u64_stats_update_begin(&r_vec->rx_sync);
		r_vec->hw_csum_rx_complete++;
		u64_stats_update_end(&r_vec->rx_sync);
		return;
	}

	if (nfp_net_rx_csum_has_errors(le16_to_cpu(rxd->rxd.flags))) {
		u64_stats_update_begin(&r_vec->rx_sync);
		r_vec->hw_csum_rx_error++;
		u64_stats_update_end(&r_vec->rx_sync);
		return;
	}

	/* Assume that the firmware will never report inner CSUM_OK unless outer
	 * L4 headers were successfully parsed. FW will always report zero UDP
	 * checksum as CSUM_OK.
	 */
	if (rxd->rxd.flags & PCIE_DESC_RX_TCP_CSUM_OK ||
	    rxd->rxd.flags & PCIE_DESC_RX_UDP_CSUM_OK) {
		__skb_incr_checksum_unnecessary(skb);
		u64_stats_update_begin(&r_vec->rx_sync);
		r_vec->hw_csum_rx_ok++;
		u64_stats_update_end(&r_vec->rx_sync);
	}

	if (rxd->rxd.flags & PCIE_DESC_RX_I_TCP_CSUM_OK ||
	    rxd->rxd.flags & PCIE_DESC_RX_I_UDP_CSUM_OK) {
		__skb_incr_checksum_unnecessary(skb);
		u64_stats_update_begin(&r_vec->rx_sync);
		r_vec->hw_csum_rx_inner_ok++;
		u64_stats_update_end(&r_vec->rx_sync);
	}
}