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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  data; } ;
struct net_device {int features; } ;
struct atl1e_rx_ring {scalar_t__ page_size; scalar_t__ rx_page_desc; } ;
struct atl1e_rx_page_desc {scalar_t__ rx_nxseq; size_t rx_using; } ;
struct atl1e_rx_page {scalar_t__* write_offset_addr; scalar_t__ read_offset; scalar_t__ addr; } ;
struct atl1e_recv_ret_status {scalar_t__ seq_num; int pkt_flag; int err_flag; scalar_t__ word1; int vtag; } ;
struct atl1e_adapter {int /*<<< orphan*/  reset_task; int /*<<< orphan*/  flags; int /*<<< orphan*/  hw; int /*<<< orphan*/  napi; struct atl1e_rx_ring rx_ring; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AT_WRITE_REGB (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int NETIF_F_RXALL ; 
 int NETIF_F_RXFCS ; 
 int /*<<< orphan*/  REG_DEBUG_DATA0 ; 
 int RRS_ERR_BAD_CRC ; 
 int RRS_ERR_CODE ; 
 int RRS_ERR_DRIBBLE ; 
 int RRS_ERR_TRUNC ; 
 int RRS_IS_ERR_FRAME ; 
 int RRS_IS_VLAN_TAG ; 
 scalar_t__ RRS_PKT_SIZE_MASK ; 
 scalar_t__ RRS_PKT_SIZE_SHIFT ; 
 int /*<<< orphan*/  __AT_DOWN ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 struct atl1e_rx_page* atl1e_get_rx_page (struct atl1e_adapter*,size_t) ; 
 int /*<<< orphan*/  atl1e_rx_checksum (struct atl1e_adapter*,struct sk_buff*,struct atl1e_recv_ret_status*) ; 
 int** atl1e_rx_page_vld_regs ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,size_t*,scalar_t__) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atl1e_clean_rx_irq(struct atl1e_adapter *adapter, u8 que,
		   int *work_done, int work_to_do)
{
	struct net_device *netdev  = adapter->netdev;
	struct atl1e_rx_ring *rx_ring = &adapter->rx_ring;
	struct atl1e_rx_page_desc *rx_page_desc =
		(struct atl1e_rx_page_desc *) rx_ring->rx_page_desc;
	struct sk_buff *skb = NULL;
	struct atl1e_rx_page *rx_page = atl1e_get_rx_page(adapter, que);
	u32 packet_size, write_offset;
	struct atl1e_recv_ret_status *prrs;

	write_offset = *(rx_page->write_offset_addr);
	if (likely(rx_page->read_offset < write_offset)) {
		do {
			if (*work_done >= work_to_do)
				break;
			(*work_done)++;
			/* get new packet's  rrs */
			prrs = (struct atl1e_recv_ret_status *) (rx_page->addr +
						 rx_page->read_offset);
			/* check sequence number */
			if (prrs->seq_num != rx_page_desc[que].rx_nxseq) {
				netdev_err(netdev,
					   "rx sequence number error (rx=%d) (expect=%d)\n",
					   prrs->seq_num,
					   rx_page_desc[que].rx_nxseq);
				rx_page_desc[que].rx_nxseq++;
				/* just for debug use */
				AT_WRITE_REG(&adapter->hw, REG_DEBUG_DATA0,
					     (((u32)prrs->seq_num) << 16) |
					     rx_page_desc[que].rx_nxseq);
				goto fatal_err;
			}
			rx_page_desc[que].rx_nxseq++;

			/* error packet */
			if ((prrs->pkt_flag & RRS_IS_ERR_FRAME) &&
			    !(netdev->features & NETIF_F_RXALL)) {
				if (prrs->err_flag & (RRS_ERR_BAD_CRC |
					RRS_ERR_DRIBBLE | RRS_ERR_CODE |
					RRS_ERR_TRUNC)) {
				/* hardware error, discard this packet*/
					netdev_err(netdev,
						   "rx packet desc error %x\n",
						   *((u32 *)prrs + 1));
					goto skip_pkt;
				}
			}

			packet_size = ((prrs->word1 >> RRS_PKT_SIZE_SHIFT) &
					RRS_PKT_SIZE_MASK);
			if (likely(!(netdev->features & NETIF_F_RXFCS)))
				packet_size -= 4; /* CRC */

			skb = netdev_alloc_skb_ip_align(netdev, packet_size);
			if (skb == NULL)
				goto skip_pkt;

			memcpy(skb->data, (u8 *)(prrs + 1), packet_size);
			skb_put(skb, packet_size);
			skb->protocol = eth_type_trans(skb, netdev);
			atl1e_rx_checksum(adapter, skb, prrs);

			if (prrs->pkt_flag & RRS_IS_VLAN_TAG) {
				u16 vlan_tag = (prrs->vtag >> 4) |
					       ((prrs->vtag & 7) << 13) |
					       ((prrs->vtag & 8) << 9);
				netdev_dbg(netdev,
					   "RXD VLAN TAG<RRD>=0x%04x\n",
					   prrs->vtag);
				__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tag);
			}
			napi_gro_receive(&adapter->napi, skb);

skip_pkt:
	/* skip current packet whether it's ok or not. */
			rx_page->read_offset +=
				(((u32)((prrs->word1 >> RRS_PKT_SIZE_SHIFT) &
				RRS_PKT_SIZE_MASK) +
				sizeof(struct atl1e_recv_ret_status) + 31) &
						0xFFFFFFE0);

			if (rx_page->read_offset >= rx_ring->page_size) {
				/* mark this page clean */
				u16 reg_addr;
				u8  rx_using;

				rx_page->read_offset =
					*(rx_page->write_offset_addr) = 0;
				rx_using = rx_page_desc[que].rx_using;
				reg_addr =
					atl1e_rx_page_vld_regs[que][rx_using];
				AT_WRITE_REGB(&adapter->hw, reg_addr, 1);
				rx_page_desc[que].rx_using ^= 1;
				rx_page = atl1e_get_rx_page(adapter, que);
			}
			write_offset = *(rx_page->write_offset_addr);
		} while (rx_page->read_offset < write_offset);
	}

	return;

fatal_err:
	if (!test_bit(__AT_DOWN, &adapter->flags))
		schedule_work(&adapter->reset_task);
}