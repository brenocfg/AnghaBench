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
typedef  int u8 ;
typedef  int u16 ;
struct sk_buff {int len; unsigned char* data; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; } ;
struct rx_pkt_attrib {scalar_t__ hdrlen; scalar_t__ iv_len; int /*<<< orphan*/ * dst; int /*<<< orphan*/ * src; } ;
struct __queue {int dummy; } ;
struct recv_priv {struct __queue free_recv_queue; } ;
struct recv_frame {struct sk_buff* pkt; struct rx_pkt_attrib attrib; } ;
struct adapter {int /*<<< orphan*/  pnetdev; struct recv_priv recvpriv; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  DBG_88E (char*,...) ; 
 int ETHERNET_HEADER_SIZE ; 
 int ETH_ALEN ; 
 int ETH_HLEN ; 
 int ETH_P_AARP ; 
 int ETH_P_IPX ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_SUBFRAME_COUNT ; 
 scalar_t__ SNAP_SIZE ; 
 int _SUCCESS ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int get_unaligned_be16 (unsigned char*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  memcmp (unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  rtw_bridge_tunnel_header ; 
 int /*<<< orphan*/  rtw_free_recvframe (struct recv_frame*,struct __queue*) ; 
 int /*<<< orphan*/  rtw_rfc1042_header ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,unsigned char*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,int) ; 

__attribute__((used)) static int amsdu_to_msdu(struct adapter *padapter, struct recv_frame *prframe)
{
	int	a_len, padding_len;
	u16	eth_type, nSubframe_Length;
	u8	nr_subframes, i;
	unsigned char *pdata;
	struct rx_pkt_attrib *pattrib;
	struct sk_buff *sub_skb, *subframes[MAX_SUBFRAME_COUNT];
	struct recv_priv *precvpriv = &padapter->recvpriv;
	struct __queue *pfree_recv_queue = &precvpriv->free_recv_queue;

	nr_subframes = 0;
	pattrib = &prframe->attrib;

	skb_pull(prframe->pkt, prframe->attrib.hdrlen);

	if (prframe->attrib.iv_len > 0)
		skb_pull(prframe->pkt, prframe->attrib.iv_len);

	a_len = prframe->pkt->len;

	pdata = prframe->pkt->data;

	while (a_len > ETH_HLEN) {
		/* Offset 12 denote 2 mac address */
		nSubframe_Length = get_unaligned_be16(pdata + 12);

		if (a_len < (ETHERNET_HEADER_SIZE + nSubframe_Length)) {
			DBG_88E("nRemain_Length is %d and nSubframe_Length is : %d\n", a_len, nSubframe_Length);
			goto exit;
		}

		/* move the data point to data content */
		pdata += ETH_HLEN;
		a_len -= ETH_HLEN;

		/* Allocate new skb for releasing to upper layer */
		sub_skb = dev_alloc_skb(nSubframe_Length + 12);
		if (sub_skb) {
			skb_reserve(sub_skb, 12);
			skb_put_data(sub_skb, pdata, nSubframe_Length);
		} else {
			sub_skb = skb_clone(prframe->pkt, GFP_ATOMIC);
			if (sub_skb) {
				sub_skb->data = pdata;
				sub_skb->len = nSubframe_Length;
				skb_set_tail_pointer(sub_skb, nSubframe_Length);
			} else {
				DBG_88E("skb_clone() Fail!!! , nr_subframes=%d\n", nr_subframes);
				break;
			}
		}

		subframes[nr_subframes++] = sub_skb;

		if (nr_subframes >= MAX_SUBFRAME_COUNT) {
			DBG_88E("ParseSubframe(): Too many Subframes! Packets dropped!\n");
			break;
		}

		pdata += nSubframe_Length;
		a_len -= nSubframe_Length;
		if (a_len != 0) {
			padding_len = 4 - ((nSubframe_Length + ETH_HLEN) & (4-1));
			if (padding_len == 4)
				padding_len = 0;

			if (a_len < padding_len)
				goto exit;

			pdata += padding_len;
			a_len -= padding_len;
		}
	}

	for (i = 0; i < nr_subframes; i++) {
		sub_skb = subframes[i];
		/* convert hdr + possible LLC headers into Ethernet header */
		eth_type = get_unaligned_be16(&sub_skb->data[6]);
		if (sub_skb->len >= 8 &&
		    ((!memcmp(sub_skb->data, rtw_rfc1042_header, SNAP_SIZE) &&
			  eth_type != ETH_P_AARP && eth_type != ETH_P_IPX) ||
			 !memcmp(sub_skb->data, rtw_bridge_tunnel_header, SNAP_SIZE))) {
			/* remove RFC1042 or Bridge-Tunnel encapsulation and replace EtherType */
			skb_pull(sub_skb, SNAP_SIZE);
			memcpy(skb_push(sub_skb, ETH_ALEN), pattrib->src, ETH_ALEN);
			memcpy(skb_push(sub_skb, ETH_ALEN), pattrib->dst, ETH_ALEN);
		} else {
			__be16 len;
			/* Leave Ethernet header part of hdr and full payload */
			len = htons(sub_skb->len);
			memcpy(skb_push(sub_skb, 2), &len, 2);
			memcpy(skb_push(sub_skb, ETH_ALEN), pattrib->src, ETH_ALEN);
			memcpy(skb_push(sub_skb, ETH_ALEN), pattrib->dst, ETH_ALEN);
		}

		/* Indicate the packets to upper layer */
		/*  Insert NAT2.5 RX here! */
		sub_skb->protocol = eth_type_trans(sub_skb, padapter->pnetdev);
		sub_skb->dev = padapter->pnetdev;

		sub_skb->ip_summed = CHECKSUM_NONE;

		netif_rx(sub_skb);
	}

exit:
	rtw_free_recvframe(prframe, pfree_recv_queue);/* free this recv_frame */

	return _SUCCESS;
}