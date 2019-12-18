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
typedef  scalar_t__ u32 ;
struct skb_shared_info {int nr_frags; int /*<<< orphan*/ * frags; } ;
struct sk_buff {scalar_t__ data; } ;
struct mlx4_wqe_data_seg {void* byte_count; void* addr; void* lkey; } ;
struct mlx4_en_tx_info {scalar_t__ map0_byte_count; int /*<<< orphan*/  map0_dma; scalar_t__ linear; } ;
struct mlx4_en_priv {struct device* ddev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  void* __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  be32_to_cpu (void*) ; 
 scalar_t__ be64_to_cpu (void*) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  skb_frag_dma_map (struct device*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/  const*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 

__attribute__((used)) static bool mlx4_en_build_dma_wqe(struct mlx4_en_priv *priv,
				  struct skb_shared_info *shinfo,
				  struct mlx4_wqe_data_seg *data,
				  struct sk_buff *skb,
				  int lso_header_size,
				  __be32 mr_key,
				  struct mlx4_en_tx_info *tx_info)
{
	struct device *ddev = priv->ddev;
	dma_addr_t dma = 0;
	u32 byte_count = 0;
	int i_frag;

	/* Map fragments if any */
	for (i_frag = shinfo->nr_frags - 1; i_frag >= 0; i_frag--) {
		const skb_frag_t *frag = &shinfo->frags[i_frag];
		byte_count = skb_frag_size(frag);
		dma = skb_frag_dma_map(ddev, frag,
				       0, byte_count,
				       DMA_TO_DEVICE);
		if (dma_mapping_error(ddev, dma))
			goto tx_drop_unmap;

		data->addr = cpu_to_be64(dma);
		data->lkey = mr_key;
		dma_wmb();
		data->byte_count = cpu_to_be32(byte_count);
		--data;
	}

	/* Map linear part if needed */
	if (tx_info->linear) {
		byte_count = skb_headlen(skb) - lso_header_size;

		dma = dma_map_single(ddev, skb->data +
				     lso_header_size, byte_count,
				     PCI_DMA_TODEVICE);
		if (dma_mapping_error(ddev, dma))
			goto tx_drop_unmap;

		data->addr = cpu_to_be64(dma);
		data->lkey = mr_key;
		dma_wmb();
		data->byte_count = cpu_to_be32(byte_count);
	}
	/* tx completion can avoid cache line miss for common cases */
	tx_info->map0_dma = dma;
	tx_info->map0_byte_count = byte_count;

	return true;

tx_drop_unmap:
	en_err(priv, "DMA mapping error\n");

	while (++i_frag < shinfo->nr_frags) {
		++data;
		dma_unmap_page(ddev, (dma_addr_t)be64_to_cpu(data->addr),
			       be32_to_cpu(data->byte_count),
			       PCI_DMA_TODEVICE);
	}

	return false;
}