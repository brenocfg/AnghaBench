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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ data; } ;
struct atl1c_tpd_desc {int word1; void* buffer_len; void* buffer_addr; } ;
struct atl1c_buffer {scalar_t__ length; void* dma; struct sk_buff* skb; } ;
struct atl1c_adapter {TYPE_2__* pdev; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  enum atl1c_trans_queue { ____Placeholder_atl1c_trans_queue } atl1c_trans_queue ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATL1C_BUFFER_BUSY ; 
 int /*<<< orphan*/  ATL1C_PCIMAP_PAGE ; 
 int /*<<< orphan*/  ATL1C_PCIMAP_SINGLE ; 
 int /*<<< orphan*/  ATL1C_PCIMAP_TODEVICE ; 
 int /*<<< orphan*/  ATL1C_SET_BUFFER_STATE (struct atl1c_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATL1C_SET_PCIMAP_TYPE (struct atl1c_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int TPD_EOP_SHIFT ; 
 int TPD_LSO_EN_MASK ; 
 int TPD_LSO_EN_SHIFT ; 
 struct atl1c_tpd_desc* atl1c_get_tpd (struct atl1c_adapter*,int) ; 
 struct atl1c_buffer* atl1c_get_tx_buffer (struct atl1c_adapter*,struct atl1c_tpd_desc*) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 void* cpu_to_le64 (void*) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  memcpy (struct atl1c_tpd_desc*,struct atl1c_tpd_desc*,int) ; 
 int /*<<< orphan*/  pci_dma_mapping_error (TYPE_2__*,void*) ; 
 void* pci_map_single (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 void* skb_frag_dma_map (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 scalar_t__ tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atl1c_tx_map(struct atl1c_adapter *adapter,
		      struct sk_buff *skb, struct atl1c_tpd_desc *tpd,
			enum atl1c_trans_queue type)
{
	struct atl1c_tpd_desc *use_tpd = NULL;
	struct atl1c_buffer *buffer_info = NULL;
	u16 buf_len = skb_headlen(skb);
	u16 map_len = 0;
	u16 mapped_len = 0;
	u16 hdr_len = 0;
	u16 nr_frags;
	u16 f;
	int tso;

	nr_frags = skb_shinfo(skb)->nr_frags;
	tso = (tpd->word1 >> TPD_LSO_EN_SHIFT) & TPD_LSO_EN_MASK;
	if (tso) {
		/* TSO */
		map_len = hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		use_tpd = tpd;

		buffer_info = atl1c_get_tx_buffer(adapter, use_tpd);
		buffer_info->length = map_len;
		buffer_info->dma = pci_map_single(adapter->pdev,
					skb->data, hdr_len, PCI_DMA_TODEVICE);
		if (unlikely(pci_dma_mapping_error(adapter->pdev,
						   buffer_info->dma)))
			goto err_dma;
		ATL1C_SET_BUFFER_STATE(buffer_info, ATL1C_BUFFER_BUSY);
		ATL1C_SET_PCIMAP_TYPE(buffer_info, ATL1C_PCIMAP_SINGLE,
			ATL1C_PCIMAP_TODEVICE);
		mapped_len += map_len;
		use_tpd->buffer_addr = cpu_to_le64(buffer_info->dma);
		use_tpd->buffer_len = cpu_to_le16(buffer_info->length);
	}

	if (mapped_len < buf_len) {
		/* mapped_len == 0, means we should use the first tpd,
		   which is given by caller  */
		if (mapped_len == 0)
			use_tpd = tpd;
		else {
			use_tpd = atl1c_get_tpd(adapter, type);
			memcpy(use_tpd, tpd, sizeof(struct atl1c_tpd_desc));
		}
		buffer_info = atl1c_get_tx_buffer(adapter, use_tpd);
		buffer_info->length = buf_len - mapped_len;
		buffer_info->dma =
			pci_map_single(adapter->pdev, skb->data + mapped_len,
					buffer_info->length, PCI_DMA_TODEVICE);
		if (unlikely(pci_dma_mapping_error(adapter->pdev,
						   buffer_info->dma)))
			goto err_dma;

		ATL1C_SET_BUFFER_STATE(buffer_info, ATL1C_BUFFER_BUSY);
		ATL1C_SET_PCIMAP_TYPE(buffer_info, ATL1C_PCIMAP_SINGLE,
			ATL1C_PCIMAP_TODEVICE);
		use_tpd->buffer_addr = cpu_to_le64(buffer_info->dma);
		use_tpd->buffer_len  = cpu_to_le16(buffer_info->length);
	}

	for (f = 0; f < nr_frags; f++) {
		skb_frag_t *frag = &skb_shinfo(skb)->frags[f];

		use_tpd = atl1c_get_tpd(adapter, type);
		memcpy(use_tpd, tpd, sizeof(struct atl1c_tpd_desc));

		buffer_info = atl1c_get_tx_buffer(adapter, use_tpd);
		buffer_info->length = skb_frag_size(frag);
		buffer_info->dma = skb_frag_dma_map(&adapter->pdev->dev,
						    frag, 0,
						    buffer_info->length,
						    DMA_TO_DEVICE);
		if (dma_mapping_error(&adapter->pdev->dev, buffer_info->dma))
			goto err_dma;

		ATL1C_SET_BUFFER_STATE(buffer_info, ATL1C_BUFFER_BUSY);
		ATL1C_SET_PCIMAP_TYPE(buffer_info, ATL1C_PCIMAP_PAGE,
			ATL1C_PCIMAP_TODEVICE);
		use_tpd->buffer_addr = cpu_to_le64(buffer_info->dma);
		use_tpd->buffer_len  = cpu_to_le16(buffer_info->length);
	}

	/* The last tpd */
	use_tpd->word1 |= 1 << TPD_EOP_SHIFT;
	/* The last buffer info contain the skb address,
	   so it will be free after unmap */
	buffer_info->skb = skb;

	return 0;

err_dma:
	buffer_info->dma = 0;
	buffer_info->length = 0;
	return -1;
}