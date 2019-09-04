#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tx_ring_desc {int map_cnt; int /*<<< orphan*/ * map; int /*<<< orphan*/  oal; } ;
struct tx_buf_desc {void* len; void* addr; } ;
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct ql_adapter {int /*<<< orphan*/  ndev; TYPE_2__* pdev; } ;
struct ob_mac_iocb_req {struct tx_buf_desc* tbd; } ;
struct oal {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TX_DESC_C ; 
 int TX_DESC_E ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (void*) ; 
 int /*<<< orphan*/  mapaddr ; 
 int /*<<< orphan*/  maplen ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_printk (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int pci_dma_mapping_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_unmap_send (struct ql_adapter*,struct tx_ring_desc*,int) ; 
 int /*<<< orphan*/  skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int skb_frag_size (int /*<<< orphan*/ *) ; 
 int skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  tx_queued ; 

__attribute__((used)) static int ql_map_send(struct ql_adapter *qdev,
		       struct ob_mac_iocb_req *mac_iocb_ptr,
		       struct sk_buff *skb, struct tx_ring_desc *tx_ring_desc)
{
	int len = skb_headlen(skb);
	dma_addr_t map;
	int frag_idx, err, map_idx = 0;
	struct tx_buf_desc *tbd = mac_iocb_ptr->tbd;
	int frag_cnt = skb_shinfo(skb)->nr_frags;

	if (frag_cnt) {
		netif_printk(qdev, tx_queued, KERN_DEBUG, qdev->ndev,
			     "frag_cnt = %d.\n", frag_cnt);
	}
	/*
	 * Map the skb buffer first.
	 */
	map = pci_map_single(qdev->pdev, skb->data, len, PCI_DMA_TODEVICE);

	err = pci_dma_mapping_error(qdev->pdev, map);
	if (err) {
		netif_err(qdev, tx_queued, qdev->ndev,
			  "PCI mapping failed with error: %d\n", err);

		return NETDEV_TX_BUSY;
	}

	tbd->len = cpu_to_le32(len);
	tbd->addr = cpu_to_le64(map);
	dma_unmap_addr_set(&tx_ring_desc->map[map_idx], mapaddr, map);
	dma_unmap_len_set(&tx_ring_desc->map[map_idx], maplen, len);
	map_idx++;

	/*
	 * This loop fills the remainder of the 8 address descriptors
	 * in the IOCB.  If there are more than 7 fragments, then the
	 * eighth address desc will point to an external list (OAL).
	 * When this happens, the remainder of the frags will be stored
	 * in this list.
	 */
	for (frag_idx = 0; frag_idx < frag_cnt; frag_idx++, map_idx++) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[frag_idx];
		tbd++;
		if (frag_idx == 6 && frag_cnt > 7) {
			/* Let's tack on an sglist.
			 * Our control block will now
			 * look like this:
			 * iocb->seg[0] = skb->data
			 * iocb->seg[1] = frag[0]
			 * iocb->seg[2] = frag[1]
			 * iocb->seg[3] = frag[2]
			 * iocb->seg[4] = frag[3]
			 * iocb->seg[5] = frag[4]
			 * iocb->seg[6] = frag[5]
			 * iocb->seg[7] = ptr to OAL (external sglist)
			 * oal->seg[0] = frag[6]
			 * oal->seg[1] = frag[7]
			 * oal->seg[2] = frag[8]
			 * oal->seg[3] = frag[9]
			 * oal->seg[4] = frag[10]
			 *      etc...
			 */
			/* Tack on the OAL in the eighth segment of IOCB. */
			map = pci_map_single(qdev->pdev, &tx_ring_desc->oal,
					     sizeof(struct oal),
					     PCI_DMA_TODEVICE);
			err = pci_dma_mapping_error(qdev->pdev, map);
			if (err) {
				netif_err(qdev, tx_queued, qdev->ndev,
					  "PCI mapping outbound address list with error: %d\n",
					  err);
				goto map_error;
			}

			tbd->addr = cpu_to_le64(map);
			/*
			 * The length is the number of fragments
			 * that remain to be mapped times the length
			 * of our sglist (OAL).
			 */
			tbd->len =
			    cpu_to_le32((sizeof(struct tx_buf_desc) *
					 (frag_cnt - frag_idx)) | TX_DESC_C);
			dma_unmap_addr_set(&tx_ring_desc->map[map_idx], mapaddr,
					   map);
			dma_unmap_len_set(&tx_ring_desc->map[map_idx], maplen,
					  sizeof(struct oal));
			tbd = (struct tx_buf_desc *)&tx_ring_desc->oal;
			map_idx++;
		}

		map = skb_frag_dma_map(&qdev->pdev->dev, frag, 0, skb_frag_size(frag),
				       DMA_TO_DEVICE);

		err = dma_mapping_error(&qdev->pdev->dev, map);
		if (err) {
			netif_err(qdev, tx_queued, qdev->ndev,
				  "PCI mapping frags failed with error: %d.\n",
				  err);
			goto map_error;
		}

		tbd->addr = cpu_to_le64(map);
		tbd->len = cpu_to_le32(skb_frag_size(frag));
		dma_unmap_addr_set(&tx_ring_desc->map[map_idx], mapaddr, map);
		dma_unmap_len_set(&tx_ring_desc->map[map_idx], maplen,
				  skb_frag_size(frag));

	}
	/* Save the number of segments we've mapped. */
	tx_ring_desc->map_cnt = map_idx;
	/* Terminate the last segment. */
	tbd->len = cpu_to_le32(le32_to_cpu(tbd->len) | TX_DESC_E);
	return NETDEV_TX_OK;

map_error:
	/*
	 * If the first frag mapping failed, then i will be zero.
	 * This causes the unmap of the skb->data area.  Otherwise
	 * we pass in the number of frags that mapped successfully
	 * so they can be umapped.
	 */
	ql_unmap_send(qdev, tx_ring_desc, map_idx);
	return NETDEV_TX_BUSY;
}