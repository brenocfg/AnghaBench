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
struct xgbe_ring_desc {int /*<<< orphan*/  desc3; int /*<<< orphan*/  desc2; void* desc1; void* desc0; } ;
struct TYPE_4__ {unsigned int packets; unsigned int bytes; } ;
struct xgbe_ring_data {int skb_dma_len; struct xgbe_ring_desc* rdesc; TYPE_1__ tx; int /*<<< orphan*/  skb_dma; } ;
struct TYPE_6__ {scalar_t__ cur_mss; scalar_t__ cur_vlan_ctag; int xmit_more; } ;
struct xgbe_packet_data {unsigned int tx_packets; unsigned int tx_bytes; scalar_t__ mss; scalar_t__ vlan_ctag; int tcp_payload_len; int tcp_header_len; int length; int rdesc_count; int /*<<< orphan*/  attributes; } ;
struct xgbe_ring {int cur; unsigned int coalesce_count; int rdesc_count; TYPE_3__ tx; struct xgbe_packet_data packet_data; } ;
struct TYPE_5__ {unsigned int tx_tso_packets; unsigned int tx_vxlan_packets; unsigned int* txq_packets; unsigned int* txq_bytes; } ;
struct xgbe_prv_data {unsigned int tx_frames; int /*<<< orphan*/  netdev; TYPE_2__ ext_stats; } ;
struct xgbe_channel {size_t queue_index; int /*<<< orphan*/  name; struct xgbe_ring* tx_ring; struct xgbe_prv_data* pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIC ; 
 int /*<<< orphan*/  CPC ; 
 int /*<<< orphan*/  CSUM_ENABLE ; 
 int /*<<< orphan*/  CTXT ; 
 int /*<<< orphan*/  DBGPR (char*,...) ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  FL ; 
 int /*<<< orphan*/  HL_B1L ; 
 int /*<<< orphan*/  IC ; 
 int /*<<< orphan*/  LD ; 
 int /*<<< orphan*/  MSS ; 
 int /*<<< orphan*/  OWN ; 
 int /*<<< orphan*/  PTP ; 
 int /*<<< orphan*/  TCMSSV ; 
 int /*<<< orphan*/  TCPHDRLEN ; 
 int /*<<< orphan*/  TCPPL ; 
 int /*<<< orphan*/  TSE ; 
 int /*<<< orphan*/  TSO_ENABLE ; 
 int /*<<< orphan*/  TTSE ; 
 int /*<<< orphan*/  TX_CONTEXT_DESC2 ; 
 int /*<<< orphan*/  TX_CONTEXT_DESC3 ; 
 int /*<<< orphan*/  TX_NORMAL_DESC2 ; 
 int TX_NORMAL_DESC2_VLAN_INSERT ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3 ; 
 int TX_NORMAL_DESC3_VXLAN_PACKET ; 
 int /*<<< orphan*/  TX_PACKET_ATTRIBUTES ; 
 int /*<<< orphan*/  VLAN_CTAG ; 
 int /*<<< orphan*/  VLTV ; 
 int /*<<< orphan*/  VNP ; 
 int /*<<< orphan*/  VT ; 
 int /*<<< orphan*/  VTIR ; 
 int /*<<< orphan*/  VXLAN ; 
 struct xgbe_ring_data* XGBE_GET_DESC_DATA (struct xgbe_ring*,int) ; 
 int XGMAC_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_SET_BITS_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  netdev_xmit_more () ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ netif_msg_tx_queued (struct xgbe_prv_data*) ; 
 scalar_t__ netif_xmit_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  tx_queued ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_dump_tx_desc (struct xgbe_prv_data*,struct xgbe_ring*,int,int,int) ; 
 int /*<<< orphan*/  xgbe_tx_start_xmit (struct xgbe_channel*,struct xgbe_ring*) ; 

__attribute__((used)) static void xgbe_dev_xmit(struct xgbe_channel *channel)
{
	struct xgbe_prv_data *pdata = channel->pdata;
	struct xgbe_ring *ring = channel->tx_ring;
	struct xgbe_ring_data *rdata;
	struct xgbe_ring_desc *rdesc;
	struct xgbe_packet_data *packet = &ring->packet_data;
	unsigned int tx_packets, tx_bytes;
	unsigned int csum, tso, vlan, vxlan;
	unsigned int tso_context, vlan_context;
	unsigned int tx_set_ic;
	int start_index = ring->cur;
	int cur_index = ring->cur;
	int i;

	DBGPR("-->xgbe_dev_xmit\n");

	tx_packets = packet->tx_packets;
	tx_bytes = packet->tx_bytes;

	csum = XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			      CSUM_ENABLE);
	tso = XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			     TSO_ENABLE);
	vlan = XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			      VLAN_CTAG);
	vxlan = XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES,
			       VXLAN);

	if (tso && (packet->mss != ring->tx.cur_mss))
		tso_context = 1;
	else
		tso_context = 0;

	if (vlan && (packet->vlan_ctag != ring->tx.cur_vlan_ctag))
		vlan_context = 1;
	else
		vlan_context = 0;

	/* Determine if an interrupt should be generated for this Tx:
	 *   Interrupt:
	 *     - Tx frame count exceeds the frame count setting
	 *     - Addition of Tx frame count to the frame count since the
	 *       last interrupt was set exceeds the frame count setting
	 *   No interrupt:
	 *     - No frame count setting specified (ethtool -C ethX tx-frames 0)
	 *     - Addition of Tx frame count to the frame count since the
	 *       last interrupt was set does not exceed the frame count setting
	 */
	ring->coalesce_count += tx_packets;
	if (!pdata->tx_frames)
		tx_set_ic = 0;
	else if (tx_packets > pdata->tx_frames)
		tx_set_ic = 1;
	else if ((ring->coalesce_count % pdata->tx_frames) < tx_packets)
		tx_set_ic = 1;
	else
		tx_set_ic = 0;

	rdata = XGBE_GET_DESC_DATA(ring, cur_index);
	rdesc = rdata->rdesc;

	/* Create a context descriptor if this is a TSO packet */
	if (tso_context || vlan_context) {
		if (tso_context) {
			netif_dbg(pdata, tx_queued, pdata->netdev,
				  "TSO context descriptor, mss=%u\n",
				  packet->mss);

			/* Set the MSS size */
			XGMAC_SET_BITS_LE(rdesc->desc2, TX_CONTEXT_DESC2,
					  MSS, packet->mss);

			/* Mark it as a CONTEXT descriptor */
			XGMAC_SET_BITS_LE(rdesc->desc3, TX_CONTEXT_DESC3,
					  CTXT, 1);

			/* Indicate this descriptor contains the MSS */
			XGMAC_SET_BITS_LE(rdesc->desc3, TX_CONTEXT_DESC3,
					  TCMSSV, 1);

			ring->tx.cur_mss = packet->mss;
		}

		if (vlan_context) {
			netif_dbg(pdata, tx_queued, pdata->netdev,
				  "VLAN context descriptor, ctag=%u\n",
				  packet->vlan_ctag);

			/* Mark it as a CONTEXT descriptor */
			XGMAC_SET_BITS_LE(rdesc->desc3, TX_CONTEXT_DESC3,
					  CTXT, 1);

			/* Set the VLAN tag */
			XGMAC_SET_BITS_LE(rdesc->desc3, TX_CONTEXT_DESC3,
					  VT, packet->vlan_ctag);

			/* Indicate this descriptor contains the VLAN tag */
			XGMAC_SET_BITS_LE(rdesc->desc3, TX_CONTEXT_DESC3,
					  VLTV, 1);

			ring->tx.cur_vlan_ctag = packet->vlan_ctag;
		}

		cur_index++;
		rdata = XGBE_GET_DESC_DATA(ring, cur_index);
		rdesc = rdata->rdesc;
	}

	/* Update buffer address (for TSO this is the header) */
	rdesc->desc0 =  cpu_to_le32(lower_32_bits(rdata->skb_dma));
	rdesc->desc1 =  cpu_to_le32(upper_32_bits(rdata->skb_dma));

	/* Update the buffer length */
	XGMAC_SET_BITS_LE(rdesc->desc2, TX_NORMAL_DESC2, HL_B1L,
			  rdata->skb_dma_len);

	/* VLAN tag insertion check */
	if (vlan)
		XGMAC_SET_BITS_LE(rdesc->desc2, TX_NORMAL_DESC2, VTIR,
				  TX_NORMAL_DESC2_VLAN_INSERT);

	/* Timestamp enablement check */
	if (XGMAC_GET_BITS(packet->attributes, TX_PACKET_ATTRIBUTES, PTP))
		XGMAC_SET_BITS_LE(rdesc->desc2, TX_NORMAL_DESC2, TTSE, 1);

	/* Mark it as First Descriptor */
	XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, FD, 1);

	/* Mark it as a NORMAL descriptor */
	XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, CTXT, 0);

	/* Set OWN bit if not the first descriptor */
	if (cur_index != start_index)
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, OWN, 1);

	if (tso) {
		/* Enable TSO */
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, TSE, 1);
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, TCPPL,
				  packet->tcp_payload_len);
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, TCPHDRLEN,
				  packet->tcp_header_len / 4);

		pdata->ext_stats.tx_tso_packets += tx_packets;
	} else {
		/* Enable CRC and Pad Insertion */
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, CPC, 0);

		/* Enable HW CSUM */
		if (csum)
			XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3,
					  CIC, 0x3);

		/* Set the total length to be transmitted */
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, FL,
				  packet->length);
	}

	if (vxlan) {
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, VNP,
				  TX_NORMAL_DESC3_VXLAN_PACKET);

		pdata->ext_stats.tx_vxlan_packets += packet->tx_packets;
	}

	for (i = cur_index - start_index + 1; i < packet->rdesc_count; i++) {
		cur_index++;
		rdata = XGBE_GET_DESC_DATA(ring, cur_index);
		rdesc = rdata->rdesc;

		/* Update buffer address */
		rdesc->desc0 = cpu_to_le32(lower_32_bits(rdata->skb_dma));
		rdesc->desc1 = cpu_to_le32(upper_32_bits(rdata->skb_dma));

		/* Update the buffer length */
		XGMAC_SET_BITS_LE(rdesc->desc2, TX_NORMAL_DESC2, HL_B1L,
				  rdata->skb_dma_len);

		/* Set OWN bit */
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, OWN, 1);

		/* Mark it as NORMAL descriptor */
		XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, CTXT, 0);

		/* Enable HW CSUM */
		if (csum)
			XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3,
					  CIC, 0x3);
	}

	/* Set LAST bit for the last descriptor */
	XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, LD, 1);

	/* Set IC bit based on Tx coalescing settings */
	if (tx_set_ic)
		XGMAC_SET_BITS_LE(rdesc->desc2, TX_NORMAL_DESC2, IC, 1);

	/* Save the Tx info to report back during cleanup */
	rdata->tx.packets = tx_packets;
	rdata->tx.bytes = tx_bytes;

	pdata->ext_stats.txq_packets[channel->queue_index] += tx_packets;
	pdata->ext_stats.txq_bytes[channel->queue_index] += tx_bytes;

	/* In case the Tx DMA engine is running, make sure everything
	 * is written to the descriptor(s) before setting the OWN bit
	 * for the first descriptor
	 */
	dma_wmb();

	/* Set OWN bit for the first descriptor */
	rdata = XGBE_GET_DESC_DATA(ring, start_index);
	rdesc = rdata->rdesc;
	XGMAC_SET_BITS_LE(rdesc->desc3, TX_NORMAL_DESC3, OWN, 1);

	if (netif_msg_tx_queued(pdata))
		xgbe_dump_tx_desc(pdata, ring, start_index,
				  packet->rdesc_count, 1);

	/* Make sure ownership is written to the descriptor */
	smp_wmb();

	ring->cur = cur_index + 1;
	if (!netdev_xmit_more() ||
	    netif_xmit_stopped(netdev_get_tx_queue(pdata->netdev,
						   channel->queue_index)))
		xgbe_tx_start_xmit(channel, ring);
	else
		ring->tx.xmit_more = 1;

	DBGPR("  %s: descriptors %u to %u written\n",
	      channel->name, start_index & (ring->rdesc_count - 1),
	      (ring->cur - 1) & (ring->rdesc_count - 1));

	DBGPR("<--xgbe_dev_xmit\n");
}