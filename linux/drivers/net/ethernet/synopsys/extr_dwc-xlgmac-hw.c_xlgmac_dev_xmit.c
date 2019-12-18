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
struct TYPE_6__ {scalar_t__ cur_mss; scalar_t__ cur_vlan_ctag; int xmit_more; } ;
struct xlgmac_pkt_info {scalar_t__ mss; scalar_t__ vlan_ctag; int tx_packets; int tcp_payload_len; int tcp_header_len; int length; int desc_count; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  attributes; } ;
struct xlgmac_ring {int cur; int coalesce_count; int dma_desc_count; TYPE_3__ tx; struct xlgmac_pkt_info pkt_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_tso_packets; int /*<<< orphan*/  tx_vlan_packets; } ;
struct xlgmac_pdata {int tx_frames; int /*<<< orphan*/  netdev; TYPE_1__ stats; } ;
struct xlgmac_dma_desc {void* desc3; void* desc2; void* desc1; void* desc0; } ;
struct TYPE_5__ {int packets; int /*<<< orphan*/  bytes; } ;
struct xlgmac_desc_data {int skb_dma_len; struct xlgmac_dma_desc* dma_desc; TYPE_2__ tx; int /*<<< orphan*/  skb_dma; } ;
struct xlgmac_channel {int /*<<< orphan*/  name; int /*<<< orphan*/  queue_index; struct xlgmac_ring* tx_ring; struct xlgmac_pdata* pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_CONTEXT_DESC2_MSS_LEN ; 
 int /*<<< orphan*/  TX_CONTEXT_DESC2_MSS_POS ; 
 int /*<<< orphan*/  TX_CONTEXT_DESC3_CTXT_LEN ; 
 int /*<<< orphan*/  TX_CONTEXT_DESC3_CTXT_POS ; 
 int /*<<< orphan*/  TX_CONTEXT_DESC3_TCMSSV_LEN ; 
 int /*<<< orphan*/  TX_CONTEXT_DESC3_TCMSSV_POS ; 
 int /*<<< orphan*/  TX_CONTEXT_DESC3_VLTV_LEN ; 
 int /*<<< orphan*/  TX_CONTEXT_DESC3_VLTV_POS ; 
 int /*<<< orphan*/  TX_CONTEXT_DESC3_VT_LEN ; 
 int /*<<< orphan*/  TX_CONTEXT_DESC3_VT_POS ; 
 int /*<<< orphan*/  TX_NORMAL_DESC2_HL_B1L_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC2_HL_B1L_POS ; 
 int /*<<< orphan*/  TX_NORMAL_DESC2_IC_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC2_IC_POS ; 
 int /*<<< orphan*/  TX_NORMAL_DESC2_TTSE_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC2_TTSE_POS ; 
 int TX_NORMAL_DESC2_VLAN_INSERT ; 
 int /*<<< orphan*/  TX_NORMAL_DESC2_VTIR_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC2_VTIR_POS ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_CIC_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_CIC_POS ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_CPC_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_CPC_POS ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_CTXT_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_CTXT_POS ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_FD_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_FD_POS ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_FL_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_FL_POS ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_LD_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_LD_POS ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_OWN_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_OWN_POS ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_TCPHDRLEN_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_TCPHDRLEN_POS ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_TCPPL_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_TCPPL_POS ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_TSE_LEN ; 
 int /*<<< orphan*/  TX_NORMAL_DESC3_TSE_POS ; 
 int /*<<< orphan*/  TX_PACKET_ATTRIBUTES_CSUM_ENABLE_LEN ; 
 int /*<<< orphan*/  TX_PACKET_ATTRIBUTES_CSUM_ENABLE_POS ; 
 int /*<<< orphan*/  TX_PACKET_ATTRIBUTES_PTP_LEN ; 
 int /*<<< orphan*/  TX_PACKET_ATTRIBUTES_PTP_POS ; 
 int /*<<< orphan*/  TX_PACKET_ATTRIBUTES_TSO_ENABLE_LEN ; 
 int /*<<< orphan*/  TX_PACKET_ATTRIBUTES_TSO_ENABLE_POS ; 
 int /*<<< orphan*/  TX_PACKET_ATTRIBUTES_VLAN_CTAG_LEN ; 
 int /*<<< orphan*/  TX_PACKET_ATTRIBUTES_VLAN_CTAG_POS ; 
 struct xlgmac_desc_data* XLGMAC_GET_DESC_DATA (struct xlgmac_ring*,int) ; 
 int XLGMAC_GET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLGMAC_PR (char*,int /*<<< orphan*/ ,int,int) ; 
 void* XLGMAC_SET_REG_BITS_LE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_xmit_more () ; 
 int /*<<< orphan*/  netif_dbg (struct xlgmac_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ netif_msg_tx_queued (struct xlgmac_pdata*) ; 
 scalar_t__ netif_xmit_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  tx_queued ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlgmac_dump_tx_desc (struct xlgmac_pdata*,struct xlgmac_ring*,int,int,int) ; 
 int /*<<< orphan*/  xlgmac_tx_start_xmit (struct xlgmac_channel*,struct xlgmac_ring*) ; 

__attribute__((used)) static void xlgmac_dev_xmit(struct xlgmac_channel *channel)
{
	struct xlgmac_pdata *pdata = channel->pdata;
	struct xlgmac_ring *ring = channel->tx_ring;
	unsigned int tso_context, vlan_context;
	struct xlgmac_desc_data *desc_data;
	struct xlgmac_dma_desc *dma_desc;
	struct xlgmac_pkt_info *pkt_info;
	unsigned int csum, tso, vlan;
	int start_index = ring->cur;
	int cur_index = ring->cur;
	unsigned int tx_set_ic;
	int i;

	pkt_info = &ring->pkt_info;
	csum = XLGMAC_GET_REG_BITS(pkt_info->attributes,
				   TX_PACKET_ATTRIBUTES_CSUM_ENABLE_POS,
				TX_PACKET_ATTRIBUTES_CSUM_ENABLE_LEN);
	tso = XLGMAC_GET_REG_BITS(pkt_info->attributes,
				  TX_PACKET_ATTRIBUTES_TSO_ENABLE_POS,
				TX_PACKET_ATTRIBUTES_TSO_ENABLE_LEN);
	vlan = XLGMAC_GET_REG_BITS(pkt_info->attributes,
				   TX_PACKET_ATTRIBUTES_VLAN_CTAG_POS,
				TX_PACKET_ATTRIBUTES_VLAN_CTAG_LEN);

	if (tso && (pkt_info->mss != ring->tx.cur_mss))
		tso_context = 1;
	else
		tso_context = 0;

	if (vlan && (pkt_info->vlan_ctag != ring->tx.cur_vlan_ctag))
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
	ring->coalesce_count += pkt_info->tx_packets;
	if (!pdata->tx_frames)
		tx_set_ic = 0;
	else if (pkt_info->tx_packets > pdata->tx_frames)
		tx_set_ic = 1;
	else if ((ring->coalesce_count % pdata->tx_frames) <
		 pkt_info->tx_packets)
		tx_set_ic = 1;
	else
		tx_set_ic = 0;

	desc_data = XLGMAC_GET_DESC_DATA(ring, cur_index);
	dma_desc = desc_data->dma_desc;

	/* Create a context descriptor if this is a TSO pkt_info */
	if (tso_context || vlan_context) {
		if (tso_context) {
			netif_dbg(pdata, tx_queued, pdata->netdev,
				  "TSO context descriptor, mss=%u\n",
				  pkt_info->mss);

			/* Set the MSS size */
			dma_desc->desc2 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc2,
						TX_CONTEXT_DESC2_MSS_POS,
						TX_CONTEXT_DESC2_MSS_LEN,
						pkt_info->mss);

			/* Mark it as a CONTEXT descriptor */
			dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc3,
						TX_CONTEXT_DESC3_CTXT_POS,
						TX_CONTEXT_DESC3_CTXT_LEN,
						1);

			/* Indicate this descriptor contains the MSS */
			dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc3,
						TX_CONTEXT_DESC3_TCMSSV_POS,
						TX_CONTEXT_DESC3_TCMSSV_LEN,
						1);

			ring->tx.cur_mss = pkt_info->mss;
		}

		if (vlan_context) {
			netif_dbg(pdata, tx_queued, pdata->netdev,
				  "VLAN context descriptor, ctag=%u\n",
				  pkt_info->vlan_ctag);

			/* Mark it as a CONTEXT descriptor */
			dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc3,
						TX_CONTEXT_DESC3_CTXT_POS,
						TX_CONTEXT_DESC3_CTXT_LEN,
						1);

			/* Set the VLAN tag */
			dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc3,
						TX_CONTEXT_DESC3_VT_POS,
						TX_CONTEXT_DESC3_VT_LEN,
						pkt_info->vlan_ctag);

			/* Indicate this descriptor contains the VLAN tag */
			dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc3,
						TX_CONTEXT_DESC3_VLTV_POS,
						TX_CONTEXT_DESC3_VLTV_LEN,
						1);

			ring->tx.cur_vlan_ctag = pkt_info->vlan_ctag;
		}

		cur_index++;
		desc_data = XLGMAC_GET_DESC_DATA(ring, cur_index);
		dma_desc = desc_data->dma_desc;
	}

	/* Update buffer address (for TSO this is the header) */
	dma_desc->desc0 =  cpu_to_le32(lower_32_bits(desc_data->skb_dma));
	dma_desc->desc1 =  cpu_to_le32(upper_32_bits(desc_data->skb_dma));

	/* Update the buffer length */
	dma_desc->desc2 = XLGMAC_SET_REG_BITS_LE(
				dma_desc->desc2,
				TX_NORMAL_DESC2_HL_B1L_POS,
				TX_NORMAL_DESC2_HL_B1L_LEN,
				desc_data->skb_dma_len);

	/* VLAN tag insertion check */
	if (vlan) {
		dma_desc->desc2 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc2,
					TX_NORMAL_DESC2_VTIR_POS,
					TX_NORMAL_DESC2_VTIR_LEN,
					TX_NORMAL_DESC2_VLAN_INSERT);
		pdata->stats.tx_vlan_packets++;
	}

	/* Timestamp enablement check */
	if (XLGMAC_GET_REG_BITS(pkt_info->attributes,
				TX_PACKET_ATTRIBUTES_PTP_POS,
				TX_PACKET_ATTRIBUTES_PTP_LEN))
		dma_desc->desc2 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc2,
					TX_NORMAL_DESC2_TTSE_POS,
					TX_NORMAL_DESC2_TTSE_LEN,
					1);

	/* Mark it as First Descriptor */
	dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
				dma_desc->desc3,
				TX_NORMAL_DESC3_FD_POS,
				TX_NORMAL_DESC3_FD_LEN,
				1);

	/* Mark it as a NORMAL descriptor */
	dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
				dma_desc->desc3,
				TX_NORMAL_DESC3_CTXT_POS,
				TX_NORMAL_DESC3_CTXT_LEN,
				0);

	/* Set OWN bit if not the first descriptor */
	if (cur_index != start_index)
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_OWN_POS,
					TX_NORMAL_DESC3_OWN_LEN,
					1);

	if (tso) {
		/* Enable TSO */
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_TSE_POS,
					TX_NORMAL_DESC3_TSE_LEN, 1);
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_TCPPL_POS,
					TX_NORMAL_DESC3_TCPPL_LEN,
					pkt_info->tcp_payload_len);
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_TCPHDRLEN_POS,
					TX_NORMAL_DESC3_TCPHDRLEN_LEN,
					pkt_info->tcp_header_len / 4);

		pdata->stats.tx_tso_packets++;
	} else {
		/* Enable CRC and Pad Insertion */
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_CPC_POS,
					TX_NORMAL_DESC3_CPC_LEN, 0);

		/* Enable HW CSUM */
		if (csum)
			dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc3,
						TX_NORMAL_DESC3_CIC_POS,
						TX_NORMAL_DESC3_CIC_LEN,
						0x3);

		/* Set the total length to be transmitted */
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_FL_POS,
					TX_NORMAL_DESC3_FL_LEN,
					pkt_info->length);
	}

	for (i = cur_index - start_index + 1; i < pkt_info->desc_count; i++) {
		cur_index++;
		desc_data = XLGMAC_GET_DESC_DATA(ring, cur_index);
		dma_desc = desc_data->dma_desc;

		/* Update buffer address */
		dma_desc->desc0 =
			cpu_to_le32(lower_32_bits(desc_data->skb_dma));
		dma_desc->desc1 =
			cpu_to_le32(upper_32_bits(desc_data->skb_dma));

		/* Update the buffer length */
		dma_desc->desc2 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc2,
					TX_NORMAL_DESC2_HL_B1L_POS,
					TX_NORMAL_DESC2_HL_B1L_LEN,
					desc_data->skb_dma_len);

		/* Set OWN bit */
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_OWN_POS,
					TX_NORMAL_DESC3_OWN_LEN, 1);

		/* Mark it as NORMAL descriptor */
		dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc3,
					TX_NORMAL_DESC3_CTXT_POS,
					TX_NORMAL_DESC3_CTXT_LEN, 0);

		/* Enable HW CSUM */
		if (csum)
			dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
						dma_desc->desc3,
						TX_NORMAL_DESC3_CIC_POS,
						TX_NORMAL_DESC3_CIC_LEN,
						0x3);
	}

	/* Set LAST bit for the last descriptor */
	dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
				dma_desc->desc3,
				TX_NORMAL_DESC3_LD_POS,
				TX_NORMAL_DESC3_LD_LEN, 1);

	/* Set IC bit based on Tx coalescing settings */
	if (tx_set_ic)
		dma_desc->desc2 = XLGMAC_SET_REG_BITS_LE(
					dma_desc->desc2,
					TX_NORMAL_DESC2_IC_POS,
					TX_NORMAL_DESC2_IC_LEN, 1);

	/* Save the Tx info to report back during cleanup */
	desc_data->tx.packets = pkt_info->tx_packets;
	desc_data->tx.bytes = pkt_info->tx_bytes;

	/* In case the Tx DMA engine is running, make sure everything
	 * is written to the descriptor(s) before setting the OWN bit
	 * for the first descriptor
	 */
	dma_wmb();

	/* Set OWN bit for the first descriptor */
	desc_data = XLGMAC_GET_DESC_DATA(ring, start_index);
	dma_desc = desc_data->dma_desc;
	dma_desc->desc3 = XLGMAC_SET_REG_BITS_LE(
				dma_desc->desc3,
				TX_NORMAL_DESC3_OWN_POS,
				TX_NORMAL_DESC3_OWN_LEN, 1);

	if (netif_msg_tx_queued(pdata))
		xlgmac_dump_tx_desc(pdata, ring, start_index,
				    pkt_info->desc_count, 1);

	/* Make sure ownership is written to the descriptor */
	smp_wmb();

	ring->cur = cur_index + 1;
	if (!netdev_xmit_more() ||
	    netif_xmit_stopped(netdev_get_tx_queue(pdata->netdev,
						   channel->queue_index)))
		xlgmac_tx_start_xmit(channel, ring);
	else
		ring->tx.xmit_more = 1;

	XLGMAC_PR("%s: descriptors %u to %u written\n",
		  channel->name, start_index & (ring->dma_desc_count - 1),
		  (ring->cur - 1) & (ring->dma_desc_count - 1));
}