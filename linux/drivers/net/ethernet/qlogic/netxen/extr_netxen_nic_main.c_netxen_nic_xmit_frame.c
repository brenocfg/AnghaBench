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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u32 ;
struct sk_buff {scalar_t__ len; } ;
struct pci_dev {int dummy; } ;
struct nx_host_tx_ring {size_t num_desc; size_t producer; struct netxen_cmd_buffer* cmd_buf_arr; struct cmd_desc_type0* desc_head; } ;
struct netxen_skb_frag {int /*<<< orphan*/  dma; int /*<<< orphan*/  length; } ;
struct netxen_cmd_buffer {int frag_count; struct netxen_skb_frag* frag_array; struct sk_buff* skb; } ;
struct TYPE_3__ {int /*<<< orphan*/  txdropped; int /*<<< orphan*/  xmitcalled; int /*<<< orphan*/  txbytes; } ;
struct netxen_adapter {TYPE_1__ stats; int /*<<< orphan*/  portnum; struct pci_dev* pdev; struct nx_host_tx_ring* tx_ring; } ;
struct net_device {int dummy; } ;
struct cmd_desc_type0 {void* addr_buffer4; void* addr_buffer3; void* addr_buffer2; void* addr_buffer1; int /*<<< orphan*/ * buffer_length; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int NETXEN_MAX_FRAGS_PER_TX ; 
 scalar_t__ TX_STOP_THRESH ; 
 int /*<<< orphan*/  __pskb_pull_tail (struct sk_buff*,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 void* get_next_index (size_t,size_t) ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netxen_clear_cmddesc (int /*<<< orphan*/ *) ; 
 scalar_t__ netxen_map_tx_skb (struct pci_dev*,struct sk_buff*,struct netxen_cmd_buffer*) ; 
 int /*<<< orphan*/  netxen_nic_update_cmd_producer (struct netxen_adapter*,struct nx_host_tx_ring*) ; 
 int /*<<< orphan*/  netxen_set_tx_frags_len (struct cmd_desc_type0*,int,scalar_t__) ; 
 int /*<<< orphan*/  netxen_set_tx_port (struct cmd_desc_type0*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netxen_tso_check (struct net_device*,struct nx_host_tx_ring*,struct cmd_desc_type0*,struct sk_buff*) ; 
 scalar_t__ netxen_tx_avail (struct nx_host_tx_ring*) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t
netxen_nic_xmit_frame(struct sk_buff *skb, struct net_device *netdev)
{
	struct netxen_adapter *adapter = netdev_priv(netdev);
	struct nx_host_tx_ring *tx_ring = adapter->tx_ring;
	struct netxen_cmd_buffer *pbuf;
	struct netxen_skb_frag *buffrag;
	struct cmd_desc_type0 *hwdesc, *first_desc;
	struct pci_dev *pdev;
	int i, k;
	int delta = 0;
	skb_frag_t *frag;

	u32 producer;
	int frag_count;
	u32 num_txd = tx_ring->num_desc;

	frag_count = skb_shinfo(skb)->nr_frags + 1;

	/* 14 frags supported for normal packet and
	 * 32 frags supported for TSO packet
	 */
	if (!skb_is_gso(skb) && frag_count > NETXEN_MAX_FRAGS_PER_TX) {

		for (i = 0; i < (frag_count - NETXEN_MAX_FRAGS_PER_TX); i++) {
			frag = &skb_shinfo(skb)->frags[i];
			delta += skb_frag_size(frag);
		}

		if (!__pskb_pull_tail(skb, delta))
			goto drop_packet;

		frag_count = 1 + skb_shinfo(skb)->nr_frags;
	}

	if (unlikely(netxen_tx_avail(tx_ring) <= TX_STOP_THRESH)) {
		netif_stop_queue(netdev);
		smp_mb();
		if (netxen_tx_avail(tx_ring) > TX_STOP_THRESH)
			netif_start_queue(netdev);
		else
			return NETDEV_TX_BUSY;
	}

	producer = tx_ring->producer;
	pbuf = &tx_ring->cmd_buf_arr[producer];

	pdev = adapter->pdev;

	if (netxen_map_tx_skb(pdev, skb, pbuf))
		goto drop_packet;

	pbuf->skb = skb;
	pbuf->frag_count = frag_count;

	first_desc = hwdesc = &tx_ring->desc_head[producer];
	netxen_clear_cmddesc((u64 *)hwdesc);

	netxen_set_tx_frags_len(first_desc, frag_count, skb->len);
	netxen_set_tx_port(first_desc, adapter->portnum);

	for (i = 0; i < frag_count; i++) {

		k = i % 4;

		if ((k == 0) && (i > 0)) {
			/* move to next desc.*/
			producer = get_next_index(producer, num_txd);
			hwdesc = &tx_ring->desc_head[producer];
			netxen_clear_cmddesc((u64 *)hwdesc);
			tx_ring->cmd_buf_arr[producer].skb = NULL;
		}

		buffrag = &pbuf->frag_array[i];

		hwdesc->buffer_length[k] = cpu_to_le16(buffrag->length);
		switch (k) {
		case 0:
			hwdesc->addr_buffer1 = cpu_to_le64(buffrag->dma);
			break;
		case 1:
			hwdesc->addr_buffer2 = cpu_to_le64(buffrag->dma);
			break;
		case 2:
			hwdesc->addr_buffer3 = cpu_to_le64(buffrag->dma);
			break;
		case 3:
			hwdesc->addr_buffer4 = cpu_to_le64(buffrag->dma);
			break;
		}
	}

	tx_ring->producer = get_next_index(producer, num_txd);

	netxen_tso_check(netdev, tx_ring, first_desc, skb);

	adapter->stats.txbytes += skb->len;
	adapter->stats.xmitcalled++;

	netxen_nic_update_cmd_producer(adapter, tx_ring);

	return NETDEV_TX_OK;

drop_packet:
	adapter->stats.txdropped++;
	dev_kfree_skb_any(skb);
	return NETDEV_TX_OK;
}