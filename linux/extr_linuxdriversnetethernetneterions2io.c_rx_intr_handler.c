#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  data; } ;
struct rx_curr_get_info {int block_index; size_t offset; } ;
struct ring_info {size_t rxd_mode; int block_count; TYPE_5__* nic; struct lro* lro0_n; scalar_t__ lro; TYPE_3__* rx_blocks; struct rx_curr_get_info rx_curr_get_info; scalar_t__ mtu; int /*<<< orphan*/  pdev; TYPE_1__* dev; int /*<<< orphan*/  rx_curr_put_info; } ;
struct lro {int /*<<< orphan*/  vlan_tag; int /*<<< orphan*/  parent; scalar_t__ in_use; } ;
struct RxD_t {scalar_t__ Host_Control; } ;
struct RxD3 {scalar_t__ Buffer2_ptr; scalar_t__ Buffer0_ptr; } ;
struct RxD1 {scalar_t__ Buffer0_ptr; } ;
typedef  int /*<<< orphan*/  put_info ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_9__ {scalar_t__ napi; } ;
struct TYPE_10__ {TYPE_4__ config; } ;
struct TYPE_8__ {struct RxD_t* block_virt_addr; TYPE_2__* rxds; } ;
struct TYPE_7__ {struct RxD_t* virt_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF0_LEN ; 
 int /*<<< orphan*/  DBG_PRINT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_DBG ; 
 scalar_t__ HEADER_802_2_SIZE ; 
 scalar_t__ HEADER_ETHERNET_II_802_3_SIZE ; 
 scalar_t__ HEADER_SNAP_SIZE ; 
 int /*<<< orphan*/  INTR_DBG ; 
 int MAX_LRO_SESSIONS ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 scalar_t__ RXD_IS_UP2DT (struct RxD_t*) ; 
 size_t RXD_MODE_1 ; 
 size_t RXD_MODE_3B ; 
 int /*<<< orphan*/  clear_lro_session (struct lro*) ; 
 int indicate_max_pkts ; 
 int /*<<< orphan*/  memcpy (struct rx_curr_get_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_rx_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_osm_handler (struct ring_info*,struct RxD_t*) ; 
 size_t* rxd_count ; 
 int /*<<< orphan*/  update_L3L4_header (TYPE_5__*,struct lro*) ; 

__attribute__((used)) static int rx_intr_handler(struct ring_info *ring_data, int budget)
{
	int get_block, put_block;
	struct rx_curr_get_info get_info, put_info;
	struct RxD_t *rxdp;
	struct sk_buff *skb;
	int pkt_cnt = 0, napi_pkts = 0;
	int i;
	struct RxD1 *rxdp1;
	struct RxD3 *rxdp3;

	if (budget <= 0)
		return napi_pkts;

	get_info = ring_data->rx_curr_get_info;
	get_block = get_info.block_index;
	memcpy(&put_info, &ring_data->rx_curr_put_info, sizeof(put_info));
	put_block = put_info.block_index;
	rxdp = ring_data->rx_blocks[get_block].rxds[get_info.offset].virt_addr;

	while (RXD_IS_UP2DT(rxdp)) {
		/*
		 * If your are next to put index then it's
		 * FIFO full condition
		 */
		if ((get_block == put_block) &&
		    (get_info.offset + 1) == put_info.offset) {
			DBG_PRINT(INTR_DBG, "%s: Ring Full\n",
				  ring_data->dev->name);
			break;
		}
		skb = (struct sk_buff *)((unsigned long)rxdp->Host_Control);
		if (skb == NULL) {
			DBG_PRINT(ERR_DBG, "%s: NULL skb in Rx Intr\n",
				  ring_data->dev->name);
			return 0;
		}
		if (ring_data->rxd_mode == RXD_MODE_1) {
			rxdp1 = (struct RxD1 *)rxdp;
			pci_unmap_single(ring_data->pdev, (dma_addr_t)
					 rxdp1->Buffer0_ptr,
					 ring_data->mtu +
					 HEADER_ETHERNET_II_802_3_SIZE +
					 HEADER_802_2_SIZE +
					 HEADER_SNAP_SIZE,
					 PCI_DMA_FROMDEVICE);
		} else if (ring_data->rxd_mode == RXD_MODE_3B) {
			rxdp3 = (struct RxD3 *)rxdp;
			pci_dma_sync_single_for_cpu(ring_data->pdev,
						    (dma_addr_t)rxdp3->Buffer0_ptr,
						    BUF0_LEN,
						    PCI_DMA_FROMDEVICE);
			pci_unmap_single(ring_data->pdev,
					 (dma_addr_t)rxdp3->Buffer2_ptr,
					 ring_data->mtu + 4,
					 PCI_DMA_FROMDEVICE);
		}
		prefetch(skb->data);
		rx_osm_handler(ring_data, rxdp);
		get_info.offset++;
		ring_data->rx_curr_get_info.offset = get_info.offset;
		rxdp = ring_data->rx_blocks[get_block].
			rxds[get_info.offset].virt_addr;
		if (get_info.offset == rxd_count[ring_data->rxd_mode]) {
			get_info.offset = 0;
			ring_data->rx_curr_get_info.offset = get_info.offset;
			get_block++;
			if (get_block == ring_data->block_count)
				get_block = 0;
			ring_data->rx_curr_get_info.block_index = get_block;
			rxdp = ring_data->rx_blocks[get_block].block_virt_addr;
		}

		if (ring_data->nic->config.napi) {
			budget--;
			napi_pkts++;
			if (!budget)
				break;
		}
		pkt_cnt++;
		if ((indicate_max_pkts) && (pkt_cnt > indicate_max_pkts))
			break;
	}
	if (ring_data->lro) {
		/* Clear all LRO sessions before exiting */
		for (i = 0; i < MAX_LRO_SESSIONS; i++) {
			struct lro *lro = &ring_data->lro0_n[i];
			if (lro->in_use) {
				update_L3L4_header(ring_data->nic, lro);
				queue_rx_frame(lro->parent, lro->vlan_tag);
				clear_lro_session(lro);
			}
		}
	}
	return napi_pkts;
}