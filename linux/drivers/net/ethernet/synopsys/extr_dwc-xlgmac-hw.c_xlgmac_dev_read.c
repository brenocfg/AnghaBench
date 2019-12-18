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
struct xlgmac_pkt_info {int vlan_ctag; void* errors; void* attributes; int /*<<< orphan*/  rss_hash_type; int /*<<< orphan*/  rss_hash; } ;
struct xlgmac_ring {int cur; int dma_desc_count; struct xlgmac_pkt_info pkt_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_split_header_packets; } ;
struct xlgmac_pdata {TYPE_1__ stats; struct net_device* netdev; } ;
struct xlgmac_dma_desc {int /*<<< orphan*/  desc0; int /*<<< orphan*/  desc3; int /*<<< orphan*/  desc1; int /*<<< orphan*/  desc2; } ;
struct TYPE_4__ {int hdr_len; int len; } ;
struct xlgmac_desc_data {TYPE_2__ rx; struct xlgmac_dma_desc* dma_desc; } ;
struct xlgmac_channel {int /*<<< orphan*/  name; struct xlgmac_ring* rx_ring; struct xlgmac_pdata* pdata; } ;
struct net_device {int features; } ;

/* Variables and functions */
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L3 ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L4 ; 
#define  RX_DESC3_L34T_IPV4_TCP 131 
#define  RX_DESC3_L34T_IPV4_UDP 130 
#define  RX_DESC3_L34T_IPV6_TCP 129 
#define  RX_DESC3_L34T_IPV6_UDP 128 
 int /*<<< orphan*/  RX_NORMAL_DESC0_OVT_LEN ; 
 int /*<<< orphan*/  RX_NORMAL_DESC0_OVT_POS ; 
 int /*<<< orphan*/  RX_NORMAL_DESC2_HL_LEN ; 
 int /*<<< orphan*/  RX_NORMAL_DESC2_HL_POS ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_CDA_LEN ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_CDA_POS ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_CTXT_LEN ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_CTXT_POS ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_ES_LEN ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_ES_POS ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_ETLT_LEN ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_ETLT_POS ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_FD_LEN ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_FD_POS ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_L34T_LEN ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_L34T_POS ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_LD_LEN ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_LD_POS ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_OWN_LEN ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_OWN_POS ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_PL_LEN ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_PL_POS ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_RSV_LEN ; 
 int /*<<< orphan*/  RX_NORMAL_DESC3_RSV_POS ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_CONTEXT_LEN ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_LEN ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_POS ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_CONTEXT_POS ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_CSUM_DONE_LEN ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_CSUM_DONE_POS ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_INCOMPLETE_LEN ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_INCOMPLETE_POS ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_RSS_HASH_LEN ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_RSS_HASH_POS ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_VLAN_CTAG_LEN ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_VLAN_CTAG_POS ; 
 int /*<<< orphan*/  RX_PACKET_ERRORS_FRAME_LEN ; 
 int /*<<< orphan*/  RX_PACKET_ERRORS_FRAME_POS ; 
 struct xlgmac_desc_data* XLGMAC_GET_DESC_DATA (struct xlgmac_ring*,int) ; 
 int XLGMAC_GET_REG_BITS_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLGMAC_PR (char*,int /*<<< orphan*/ ,int,int) ; 
 void* XLGMAC_SET_REG_BITS (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct xlgmac_pdata*,int /*<<< orphan*/ ,struct net_device*,char*,int,...) ; 
 scalar_t__ netif_msg_rx_status (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  rx_status ; 
 int /*<<< orphan*/  xlgmac_dump_rx_desc (struct xlgmac_pdata*,struct xlgmac_ring*,int) ; 
 int /*<<< orphan*/  xlgmac_get_rx_tstamp (struct xlgmac_pkt_info*,struct xlgmac_dma_desc*) ; 

__attribute__((used)) static int xlgmac_dev_read(struct xlgmac_channel *channel)
{
	struct xlgmac_pdata *pdata = channel->pdata;
	struct xlgmac_ring *ring = channel->rx_ring;
	struct net_device *netdev = pdata->netdev;
	struct xlgmac_desc_data *desc_data;
	struct xlgmac_dma_desc *dma_desc;
	struct xlgmac_pkt_info *pkt_info;
	unsigned int err, etlt, l34t;

	desc_data = XLGMAC_GET_DESC_DATA(ring, ring->cur);
	dma_desc = desc_data->dma_desc;
	pkt_info = &ring->pkt_info;

	/* Check for data availability */
	if (XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				   RX_NORMAL_DESC3_OWN_POS,
				   RX_NORMAL_DESC3_OWN_LEN))
		return 1;

	/* Make sure descriptor fields are read after reading the OWN bit */
	dma_rmb();

	if (netif_msg_rx_status(pdata))
		xlgmac_dump_rx_desc(pdata, ring, ring->cur);

	if (XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				   RX_NORMAL_DESC3_CTXT_POS,
				   RX_NORMAL_DESC3_CTXT_LEN)) {
		/* Timestamp Context Descriptor */
		xlgmac_get_rx_tstamp(pkt_info, dma_desc);

		pkt_info->attributes = XLGMAC_SET_REG_BITS(
					pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_CONTEXT_POS,
					RX_PACKET_ATTRIBUTES_CONTEXT_LEN,
					1);
		pkt_info->attributes = XLGMAC_SET_REG_BITS(
				pkt_info->attributes,
				RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_POS,
				RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_LEN,
				0);
		return 0;
	}

	/* Normal Descriptor, be sure Context Descriptor bit is off */
	pkt_info->attributes = XLGMAC_SET_REG_BITS(
				pkt_info->attributes,
				RX_PACKET_ATTRIBUTES_CONTEXT_POS,
				RX_PACKET_ATTRIBUTES_CONTEXT_LEN,
				0);

	/* Indicate if a Context Descriptor is next */
	if (XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				   RX_NORMAL_DESC3_CDA_POS,
				   RX_NORMAL_DESC3_CDA_LEN))
		pkt_info->attributes = XLGMAC_SET_REG_BITS(
				pkt_info->attributes,
				RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_POS,
				RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_LEN,
				1);

	/* Get the header length */
	if (XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				   RX_NORMAL_DESC3_FD_POS,
				   RX_NORMAL_DESC3_FD_LEN)) {
		desc_data->rx.hdr_len = XLGMAC_GET_REG_BITS_LE(dma_desc->desc2,
							RX_NORMAL_DESC2_HL_POS,
							RX_NORMAL_DESC2_HL_LEN);
		if (desc_data->rx.hdr_len)
			pdata->stats.rx_split_header_packets++;
	}

	/* Get the RSS hash */
	if (XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				   RX_NORMAL_DESC3_RSV_POS,
				   RX_NORMAL_DESC3_RSV_LEN)) {
		pkt_info->attributes = XLGMAC_SET_REG_BITS(
				pkt_info->attributes,
				RX_PACKET_ATTRIBUTES_RSS_HASH_POS,
				RX_PACKET_ATTRIBUTES_RSS_HASH_LEN,
				1);

		pkt_info->rss_hash = le32_to_cpu(dma_desc->desc1);

		l34t = XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
					      RX_NORMAL_DESC3_L34T_POS,
					  RX_NORMAL_DESC3_L34T_LEN);
		switch (l34t) {
		case RX_DESC3_L34T_IPV4_TCP:
		case RX_DESC3_L34T_IPV4_UDP:
		case RX_DESC3_L34T_IPV6_TCP:
		case RX_DESC3_L34T_IPV6_UDP:
			pkt_info->rss_hash_type = PKT_HASH_TYPE_L4;
			break;
		default:
			pkt_info->rss_hash_type = PKT_HASH_TYPE_L3;
		}
	}

	/* Get the pkt_info length */
	desc_data->rx.len = XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
					RX_NORMAL_DESC3_PL_POS,
					RX_NORMAL_DESC3_PL_LEN);

	if (!XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				    RX_NORMAL_DESC3_LD_POS,
				    RX_NORMAL_DESC3_LD_LEN)) {
		/* Not all the data has been transferred for this pkt_info */
		pkt_info->attributes = XLGMAC_SET_REG_BITS(
				pkt_info->attributes,
				RX_PACKET_ATTRIBUTES_INCOMPLETE_POS,
				RX_PACKET_ATTRIBUTES_INCOMPLETE_LEN,
				1);
		return 0;
	}

	/* This is the last of the data for this pkt_info */
	pkt_info->attributes = XLGMAC_SET_REG_BITS(
			pkt_info->attributes,
			RX_PACKET_ATTRIBUTES_INCOMPLETE_POS,
			RX_PACKET_ATTRIBUTES_INCOMPLETE_LEN,
			0);

	/* Set checksum done indicator as appropriate */
	if (netdev->features & NETIF_F_RXCSUM)
		pkt_info->attributes = XLGMAC_SET_REG_BITS(
				pkt_info->attributes,
				RX_PACKET_ATTRIBUTES_CSUM_DONE_POS,
				RX_PACKET_ATTRIBUTES_CSUM_DONE_LEN,
				1);

	/* Check for errors (only valid in last descriptor) */
	err = XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				     RX_NORMAL_DESC3_ES_POS,
				     RX_NORMAL_DESC3_ES_LEN);
	etlt = XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				      RX_NORMAL_DESC3_ETLT_POS,
				      RX_NORMAL_DESC3_ETLT_LEN);
	netif_dbg(pdata, rx_status, netdev, "err=%u, etlt=%#x\n", err, etlt);

	if (!err || !etlt) {
		/* No error if err is 0 or etlt is 0 */
		if ((etlt == 0x09) &&
		    (netdev->features & NETIF_F_HW_VLAN_CTAG_RX)) {
			pkt_info->attributes = XLGMAC_SET_REG_BITS(
					pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_VLAN_CTAG_POS,
					RX_PACKET_ATTRIBUTES_VLAN_CTAG_LEN,
					1);
			pkt_info->vlan_ctag =
				XLGMAC_GET_REG_BITS_LE(dma_desc->desc0,
						       RX_NORMAL_DESC0_OVT_POS,
						   RX_NORMAL_DESC0_OVT_LEN);
			netif_dbg(pdata, rx_status, netdev, "vlan-ctag=%#06x\n",
				  pkt_info->vlan_ctag);
		}
	} else {
		if ((etlt == 0x05) || (etlt == 0x06))
			pkt_info->attributes = XLGMAC_SET_REG_BITS(
					pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_CSUM_DONE_POS,
					RX_PACKET_ATTRIBUTES_CSUM_DONE_LEN,
					0);
		else
			pkt_info->errors = XLGMAC_SET_REG_BITS(
					pkt_info->errors,
					RX_PACKET_ERRORS_FRAME_POS,
					RX_PACKET_ERRORS_FRAME_LEN,
					1);
	}

	XLGMAC_PR("%s - descriptor=%u (cur=%d)\n", channel->name,
		  ring->cur & (ring->dma_desc_count - 1), ring->cur);

	return 0;
}