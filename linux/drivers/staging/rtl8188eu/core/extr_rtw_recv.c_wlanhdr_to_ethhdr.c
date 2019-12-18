#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct rx_pkt_attrib {int hdrlen; int iv_len; int* dst; int* src; scalar_t__ eth_type; scalar_t__ icv_len; scalar_t__ encrypt; } ;
struct recv_frame {TYPE_1__* pkt; struct rx_pkt_attrib attrib; } ;
typedef  int ieee80211_snap_hdr ;
struct ethhdr {int dummy; } ;
typedef  int __be16 ;
struct TYPE_3__ {int* data; scalar_t__ len; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SNAP_ETH_TYPE_APPLETALK_AARP ; 
 int /*<<< orphan*/  SNAP_ETH_TYPE_IPX ; 
 int SNAP_SIZE ; 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_recv_c_ ; 
 int htons (scalar_t__) ; 
 scalar_t__ memcmp (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 scalar_t__ ntohs (int) ; 
 int /*<<< orphan*/  rtw_bridge_tunnel_header ; 
 int /*<<< orphan*/  rtw_rfc1042_header ; 
 int* skb_pull (TYPE_1__*,int) ; 
 int /*<<< orphan*/  skb_trim (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int wlanhdr_to_ethhdr(struct recv_frame *precvframe)
{
	int	rmv_len;
	u16	eth_type, len;
	__be16 be_tmp;
	u8	bsnaphdr;
	u8	*psnap_type;
	struct ieee80211_snap_hdr	*psnap;

	u8 *ptr = precvframe->pkt->data;
	struct rx_pkt_attrib *pattrib = &precvframe->attrib;

	if (pattrib->encrypt)
		skb_trim(precvframe->pkt, precvframe->pkt->len - pattrib->icv_len);

	psnap = (struct ieee80211_snap_hdr *)(ptr+pattrib->hdrlen + pattrib->iv_len);
	psnap_type = ptr+pattrib->hdrlen + pattrib->iv_len+SNAP_SIZE;
	/* convert hdr + possible LLC headers into Ethernet header */
	if ((!memcmp(psnap, rtw_rfc1042_header, SNAP_SIZE) &&
	     memcmp(psnap_type, SNAP_ETH_TYPE_IPX, 2) &&
	     memcmp(psnap_type, SNAP_ETH_TYPE_APPLETALK_AARP, 2)) ||
	     !memcmp(psnap, rtw_bridge_tunnel_header, SNAP_SIZE)) {
		/* remove RFC1042 or Bridge-Tunnel encapsulation and replace EtherType */
		bsnaphdr = true;
	} else {
		/* Leave Ethernet header part of hdr and full payload */
		bsnaphdr = false;
	}

	rmv_len = pattrib->hdrlen + pattrib->iv_len + (bsnaphdr ? SNAP_SIZE : 0);
	len = precvframe->pkt->len - rmv_len;

	RT_TRACE(_module_rtl871x_recv_c_, _drv_info_,
		 ("\n===pattrib->hdrlen: %x,  pattrib->iv_len:%x===\n\n", pattrib->hdrlen,  pattrib->iv_len));

	memcpy(&be_tmp, ptr+rmv_len, 2);
	eth_type = ntohs(be_tmp); /* pattrib->ether_type */
	pattrib->eth_type = eth_type;

	ptr = skb_pull(precvframe->pkt, rmv_len - sizeof(struct ethhdr) + (bsnaphdr ? 2 : 0));
	if (!ptr)
		return _FAIL;

	memcpy(ptr, pattrib->dst, ETH_ALEN);
	memcpy(ptr + ETH_ALEN, pattrib->src, ETH_ALEN);

	if (!bsnaphdr) {
		be_tmp = htons(len);
		memcpy(ptr + 12, &be_tmp, 2);
	}

	return _SUCCESS;
}