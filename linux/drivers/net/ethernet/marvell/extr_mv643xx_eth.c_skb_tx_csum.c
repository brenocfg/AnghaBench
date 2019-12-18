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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ protocol; scalar_t__ data; } ;
struct mv643xx_eth_private {TYPE_1__* shared; } ;
struct TYPE_4__ {int ihl; int protocol; } ;
struct TYPE_3__ {int tx_csum_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CHECKSUM_PARTIAL ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int GEN_IP_V4_CHECKSUM ; 
 int GEN_TCP_UDP_CHECKSUM ; 
 int GEN_TCP_UDP_CHK_FULL ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int MAC_HDR_EXTRA_4_BYTES ; 
 int MAC_HDR_EXTRA_8_BYTES ; 
 int TX_IHL_SHIFT ; 
 int UDP_FRAME ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_2__* ip_hdr (struct sk_buff*) ; 
 int skb_checksum_help (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int skb_tx_csum(struct mv643xx_eth_private *mp, struct sk_buff *skb,
		       u16 *l4i_chk, u32 *command, int length)
{
	int ret;
	u32 cmd = 0;

	if (skb->ip_summed == CHECKSUM_PARTIAL) {
		int hdr_len;
		int tag_bytes;

		BUG_ON(skb->protocol != htons(ETH_P_IP) &&
		       skb->protocol != htons(ETH_P_8021Q));

		hdr_len = (void *)ip_hdr(skb) - (void *)skb->data;
		tag_bytes = hdr_len - ETH_HLEN;

		if (length - hdr_len > mp->shared->tx_csum_limit ||
		    unlikely(tag_bytes & ~12)) {
			ret = skb_checksum_help(skb);
			if (!ret)
				goto no_csum;
			return ret;
		}

		if (tag_bytes & 4)
			cmd |= MAC_HDR_EXTRA_4_BYTES;
		if (tag_bytes & 8)
			cmd |= MAC_HDR_EXTRA_8_BYTES;

		cmd |= GEN_TCP_UDP_CHECKSUM | GEN_TCP_UDP_CHK_FULL |
			   GEN_IP_V4_CHECKSUM   |
			   ip_hdr(skb)->ihl << TX_IHL_SHIFT;

		/* TODO: Revisit this. With the usage of GEN_TCP_UDP_CHK_FULL
		 * it seems we don't need to pass the initial checksum. */
		switch (ip_hdr(skb)->protocol) {
		case IPPROTO_UDP:
			cmd |= UDP_FRAME;
			*l4i_chk = 0;
			break;
		case IPPROTO_TCP:
			*l4i_chk = 0;
			break;
		default:
			WARN(1, "protocol not supported");
		}
	} else {
no_csum:
		/* Errata BTS #50, IHL must be 5 if no HW checksum */
		cmd |= 5 << TX_IHL_SHIFT;
	}
	*command = cmd;
	return 0;
}