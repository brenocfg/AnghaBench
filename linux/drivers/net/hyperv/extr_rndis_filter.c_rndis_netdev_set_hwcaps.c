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
struct rndis_device {struct net_device* ndev; } ;
struct netvsc_device {int dummy; } ;
struct net_device_context {int /*<<< orphan*/  tx_checksum_mask; } ;
struct net_device {int hw_features; int features; } ;
struct ndis_offload_params {void* rsc_ip_v6; void* rsc_ip_v4; void* udp_ip_v6_csum; void* lso_v2_ipv6; void* tcp_ip_v6_csum; void* udp_ip_v4_csum; void* lso_v2_ipv4; void* tcp_ip_v4_csum; int /*<<< orphan*/  ip_v4_csum; } ;
struct TYPE_6__ {scalar_t__ ip6; scalar_t__ ip4; } ;
struct TYPE_5__ {int ip4_txcsum; int ip6_txcsum; } ;
struct TYPE_4__ {int ip4_encap; unsigned int ip4_maxsz; int ip6_encap; int ip6_opts; unsigned int ip6_maxsz; } ;
struct ndis_offload {TYPE_3__ rsc; TYPE_2__ csum; TYPE_1__ lsov2; } ;

/* Variables and functions */
 unsigned int GSO_MAX_SIZE ; 
 int NDIS_LSOV2_CAP_IP6 ; 
 int NDIS_OFFLOAD_ENCAP_8023 ; 
 void* NDIS_OFFLOAD_PARAMETERS_LSOV2_ENABLED ; 
 void* NDIS_OFFLOAD_PARAMETERS_RSC_DISABLED ; 
 void* NDIS_OFFLOAD_PARAMETERS_RSC_ENABLED ; 
 int /*<<< orphan*/  NDIS_OFFLOAD_PARAMETERS_TX_RX_DISABLED ; 
 void* NDIS_OFFLOAD_PARAMETERS_TX_RX_ENABLED ; 
 int NDIS_TXCSUM_ALL_TCP4 ; 
 int NDIS_TXCSUM_ALL_TCP6 ; 
 int NDIS_TXCSUM_CAP_UDP4 ; 
 int NDIS_TXCSUM_CAP_UDP6 ; 
 int NETIF_F_IPV6_CSUM ; 
 int NETIF_F_IP_CSUM ; 
 int NETIF_F_LRO ; 
 int NETIF_F_RXCSUM ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int NETIF_F_TSO6 ; 
 int NETVSC_SUPPORTED_HW_FEATURES ; 
 int /*<<< orphan*/  TRANSPORT_INFO_IPV4_TCP ; 
 int /*<<< orphan*/  TRANSPORT_INFO_IPV4_UDP ; 
 int /*<<< orphan*/  TRANSPORT_INFO_IPV6_TCP ; 
 int /*<<< orphan*/  TRANSPORT_INFO_IPV6_UDP ; 
 int /*<<< orphan*/  memset (struct ndis_offload_params*,int /*<<< orphan*/ ,int) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_set_gso_max_size (struct net_device*,unsigned int) ; 
 int rndis_filter_set_offload_params (struct net_device*,struct netvsc_device*,struct ndis_offload_params*) ; 
 int rndis_query_hwcaps (struct rndis_device*,struct netvsc_device*,struct ndis_offload*) ; 

__attribute__((used)) static int rndis_netdev_set_hwcaps(struct rndis_device *rndis_device,
				   struct netvsc_device *nvdev)
{
	struct net_device *net = rndis_device->ndev;
	struct net_device_context *net_device_ctx = netdev_priv(net);
	struct ndis_offload hwcaps;
	struct ndis_offload_params offloads;
	unsigned int gso_max_size = GSO_MAX_SIZE;
	int ret;

	/* Find HW offload capabilities */
	ret = rndis_query_hwcaps(rndis_device, nvdev, &hwcaps);
	if (ret != 0)
		return ret;

	/* A value of zero means "no change"; now turn on what we want. */
	memset(&offloads, 0, sizeof(struct ndis_offload_params));

	/* Linux does not care about IP checksum, always does in kernel */
	offloads.ip_v4_csum = NDIS_OFFLOAD_PARAMETERS_TX_RX_DISABLED;

	/* Reset previously set hw_features flags */
	net->hw_features &= ~NETVSC_SUPPORTED_HW_FEATURES;
	net_device_ctx->tx_checksum_mask = 0;

	/* Compute tx offload settings based on hw capabilities */
	net->hw_features |= NETIF_F_RXCSUM;
	net->hw_features |= NETIF_F_SG;

	if ((hwcaps.csum.ip4_txcsum & NDIS_TXCSUM_ALL_TCP4) == NDIS_TXCSUM_ALL_TCP4) {
		/* Can checksum TCP */
		net->hw_features |= NETIF_F_IP_CSUM;
		net_device_ctx->tx_checksum_mask |= TRANSPORT_INFO_IPV4_TCP;

		offloads.tcp_ip_v4_csum = NDIS_OFFLOAD_PARAMETERS_TX_RX_ENABLED;

		if (hwcaps.lsov2.ip4_encap & NDIS_OFFLOAD_ENCAP_8023) {
			offloads.lso_v2_ipv4 = NDIS_OFFLOAD_PARAMETERS_LSOV2_ENABLED;
			net->hw_features |= NETIF_F_TSO;

			if (hwcaps.lsov2.ip4_maxsz < gso_max_size)
				gso_max_size = hwcaps.lsov2.ip4_maxsz;
		}

		if (hwcaps.csum.ip4_txcsum & NDIS_TXCSUM_CAP_UDP4) {
			offloads.udp_ip_v4_csum = NDIS_OFFLOAD_PARAMETERS_TX_RX_ENABLED;
			net_device_ctx->tx_checksum_mask |= TRANSPORT_INFO_IPV4_UDP;
		}
	}

	if ((hwcaps.csum.ip6_txcsum & NDIS_TXCSUM_ALL_TCP6) == NDIS_TXCSUM_ALL_TCP6) {
		net->hw_features |= NETIF_F_IPV6_CSUM;

		offloads.tcp_ip_v6_csum = NDIS_OFFLOAD_PARAMETERS_TX_RX_ENABLED;
		net_device_ctx->tx_checksum_mask |= TRANSPORT_INFO_IPV6_TCP;

		if ((hwcaps.lsov2.ip6_encap & NDIS_OFFLOAD_ENCAP_8023) &&
		    (hwcaps.lsov2.ip6_opts & NDIS_LSOV2_CAP_IP6) == NDIS_LSOV2_CAP_IP6) {
			offloads.lso_v2_ipv6 = NDIS_OFFLOAD_PARAMETERS_LSOV2_ENABLED;
			net->hw_features |= NETIF_F_TSO6;

			if (hwcaps.lsov2.ip6_maxsz < gso_max_size)
				gso_max_size = hwcaps.lsov2.ip6_maxsz;
		}

		if (hwcaps.csum.ip6_txcsum & NDIS_TXCSUM_CAP_UDP6) {
			offloads.udp_ip_v6_csum = NDIS_OFFLOAD_PARAMETERS_TX_RX_ENABLED;
			net_device_ctx->tx_checksum_mask |= TRANSPORT_INFO_IPV6_UDP;
		}
	}

	if (hwcaps.rsc.ip4 && hwcaps.rsc.ip6) {
		net->hw_features |= NETIF_F_LRO;

		if (net->features & NETIF_F_LRO) {
			offloads.rsc_ip_v4 = NDIS_OFFLOAD_PARAMETERS_RSC_ENABLED;
			offloads.rsc_ip_v6 = NDIS_OFFLOAD_PARAMETERS_RSC_ENABLED;
		} else {
			offloads.rsc_ip_v4 = NDIS_OFFLOAD_PARAMETERS_RSC_DISABLED;
			offloads.rsc_ip_v6 = NDIS_OFFLOAD_PARAMETERS_RSC_DISABLED;
		}
	}

	/* In case some hw_features disappeared we need to remove them from
	 * net->features list as they're no longer supported.
	 */
	net->features &= ~NETVSC_SUPPORTED_HW_FEATURES | net->hw_features;

	netif_set_gso_max_size(net, gso_max_size);

	ret = rndis_filter_set_offload_params(net, nvdev, &offloads);

	return ret;
}