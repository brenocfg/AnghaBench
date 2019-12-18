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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct be_wrb_params {int /*<<< orphan*/  features; int /*<<< orphan*/  vlan_tag; int /*<<< orphan*/  lso_mss; } ;
struct be_eth_hdr_wrb {int dummy; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_WRB_F_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRC ; 
 int /*<<< orphan*/  IPCS ; 
 int /*<<< orphan*/  LSO ; 
 int /*<<< orphan*/  LSO6 ; 
 int /*<<< orphan*/  OS2BMC ; 
 int /*<<< orphan*/  SET_TX_WRB_HDR_BITS (int /*<<< orphan*/ ,struct be_eth_hdr_wrb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCPCS ; 
 int /*<<< orphan*/  UDPCS ; 
 int /*<<< orphan*/  VLAN ; 
 int /*<<< orphan*/  VLAN_SKIP_HW ; 
 int /*<<< orphan*/  crc ; 
 int /*<<< orphan*/  event ; 
 int /*<<< orphan*/  ipcs ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  lso ; 
 int /*<<< orphan*/  lso6 ; 
 int /*<<< orphan*/  lso_mss ; 
 int /*<<< orphan*/  memset (struct be_eth_hdr_wrb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mgmt ; 
 int /*<<< orphan*/  num_wrb ; 
 int /*<<< orphan*/  skb_wrb_cnt (struct sk_buff*) ; 
 int /*<<< orphan*/  tcpcs ; 
 int /*<<< orphan*/  udpcs ; 
 int /*<<< orphan*/  vlan ; 
 int /*<<< orphan*/  vlan_tag ; 

__attribute__((used)) static void wrb_fill_hdr(struct be_adapter *adapter,
			 struct be_eth_hdr_wrb *hdr,
			 struct be_wrb_params *wrb_params,
			 struct sk_buff *skb)
{
	memset(hdr, 0, sizeof(*hdr));

	SET_TX_WRB_HDR_BITS(crc, hdr,
			    BE_WRB_F_GET(wrb_params->features, CRC));
	SET_TX_WRB_HDR_BITS(ipcs, hdr,
			    BE_WRB_F_GET(wrb_params->features, IPCS));
	SET_TX_WRB_HDR_BITS(tcpcs, hdr,
			    BE_WRB_F_GET(wrb_params->features, TCPCS));
	SET_TX_WRB_HDR_BITS(udpcs, hdr,
			    BE_WRB_F_GET(wrb_params->features, UDPCS));

	SET_TX_WRB_HDR_BITS(lso, hdr,
			    BE_WRB_F_GET(wrb_params->features, LSO));
	SET_TX_WRB_HDR_BITS(lso6, hdr,
			    BE_WRB_F_GET(wrb_params->features, LSO6));
	SET_TX_WRB_HDR_BITS(lso_mss, hdr, wrb_params->lso_mss);

	/* Hack to skip HW VLAN tagging needs evt = 1, compl = 0. When this
	 * hack is not needed, the evt bit is set while ringing DB.
	 */
	SET_TX_WRB_HDR_BITS(event, hdr,
			    BE_WRB_F_GET(wrb_params->features, VLAN_SKIP_HW));
	SET_TX_WRB_HDR_BITS(vlan, hdr,
			    BE_WRB_F_GET(wrb_params->features, VLAN));
	SET_TX_WRB_HDR_BITS(vlan_tag, hdr, wrb_params->vlan_tag);

	SET_TX_WRB_HDR_BITS(num_wrb, hdr, skb_wrb_cnt(skb));
	SET_TX_WRB_HDR_BITS(len, hdr, skb->len);
	SET_TX_WRB_HDR_BITS(mgmt, hdr,
			    BE_WRB_F_GET(wrb_params->features, OS2BMC));
}