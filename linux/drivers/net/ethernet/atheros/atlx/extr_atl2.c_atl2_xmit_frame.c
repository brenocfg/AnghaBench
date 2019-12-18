#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct tx_pkt_header {int pkt_size; int ins_vlan; int vlan; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct atl2_adapter {int txd_write_ptr; int txd_ring_size; size_t txs_next_clear; size_t txs_ring_size; int /*<<< orphan*/  hw; TYPE_1__* txs_ring; scalar_t__ txd_ring; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {scalar_t__ update; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATL2_WRITE_REGW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  REG_MB_TXD_WR_IDX ; 
 int TxdFreeBytes (struct atl2_adapter*) ; 
 int TxsFreeUnit (struct atl2_adapter*) ; 
 int /*<<< orphan*/  __ATL2_DOWN ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 struct atl2_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t atl2_xmit_frame(struct sk_buff *skb,
					 struct net_device *netdev)
{
	struct atl2_adapter *adapter = netdev_priv(netdev);
	struct tx_pkt_header *txph;
	u32 offset, copy_len;
	int txs_unused;
	int txbuf_unused;

	if (test_bit(__ATL2_DOWN, &adapter->flags)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	if (unlikely(skb->len <= 0)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	txs_unused = TxsFreeUnit(adapter);
	txbuf_unused = TxdFreeBytes(adapter);

	if (skb->len + sizeof(struct tx_pkt_header) + 4  > txbuf_unused ||
		txs_unused < 1) {
		/* not enough resources */
		netif_stop_queue(netdev);
		return NETDEV_TX_BUSY;
	}

	offset = adapter->txd_write_ptr;

	txph = (struct tx_pkt_header *) (((u8 *)adapter->txd_ring) + offset);

	*(u32 *)txph = 0;
	txph->pkt_size = skb->len;

	offset += 4;
	if (offset >= adapter->txd_ring_size)
		offset -= adapter->txd_ring_size;
	copy_len = adapter->txd_ring_size - offset;
	if (copy_len >= skb->len) {
		memcpy(((u8 *)adapter->txd_ring) + offset, skb->data, skb->len);
		offset += ((u32)(skb->len + 3) & ~3);
	} else {
		memcpy(((u8 *)adapter->txd_ring)+offset, skb->data, copy_len);
		memcpy((u8 *)adapter->txd_ring, skb->data+copy_len,
			skb->len-copy_len);
		offset = ((u32)(skb->len-copy_len + 3) & ~3);
	}
#ifdef NETIF_F_HW_VLAN_CTAG_TX
	if (skb_vlan_tag_present(skb)) {
		u16 vlan_tag = skb_vlan_tag_get(skb);
		vlan_tag = (vlan_tag << 4) |
			(vlan_tag >> 13) |
			((vlan_tag >> 9) & 0x8);
		txph->ins_vlan = 1;
		txph->vlan = vlan_tag;
	}
#endif
	if (offset >= adapter->txd_ring_size)
		offset -= adapter->txd_ring_size;
	adapter->txd_write_ptr = offset;

	/* clear txs before send */
	adapter->txs_ring[adapter->txs_next_clear].update = 0;
	if (++adapter->txs_next_clear == adapter->txs_ring_size)
		adapter->txs_next_clear = 0;

	ATL2_WRITE_REGW(&adapter->hw, REG_MB_TXD_WR_IDX,
		(adapter->txd_write_ptr >> 2));

	dev_consume_skb_any(skb);
	return NETDEV_TX_OK;
}