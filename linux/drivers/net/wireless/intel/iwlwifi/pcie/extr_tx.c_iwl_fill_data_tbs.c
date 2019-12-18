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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ data; } ;
struct iwl_txq {int dummy; } ;
struct iwl_trans {int /*<<< orphan*/  dev; } ;
struct iwl_cmd_meta {int /*<<< orphan*/  tbs; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_pcie_txq_build_tfd (struct iwl_trans*,struct iwl_txq*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ skb_frag_address (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  skb_frag_dma_map (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/  const*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  trace_iwlwifi_dev_tx_tb (int /*<<< orphan*/ ,struct sk_buff*,scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_fill_data_tbs(struct iwl_trans *trans, struct sk_buff *skb,
			     struct iwl_txq *txq, u8 hdr_len,
			     struct iwl_cmd_meta *out_meta)
{
	u16 head_tb_len;
	int i;

	/*
	 * Set up TFD's third entry to point directly to remainder
	 * of skb's head, if any
	 */
	head_tb_len = skb_headlen(skb) - hdr_len;

	if (head_tb_len > 0) {
		dma_addr_t tb_phys = dma_map_single(trans->dev,
						    skb->data + hdr_len,
						    head_tb_len, DMA_TO_DEVICE);
		if (unlikely(dma_mapping_error(trans->dev, tb_phys)))
			return -EINVAL;
		trace_iwlwifi_dev_tx_tb(trans->dev, skb,
					skb->data + hdr_len,
					head_tb_len);
		iwl_pcie_txq_build_tfd(trans, txq, tb_phys, head_tb_len, false);
	}

	/* set up the remaining entries to point to the data */
	for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		dma_addr_t tb_phys;
		int tb_idx;

		if (!skb_frag_size(frag))
			continue;

		tb_phys = skb_frag_dma_map(trans->dev, frag, 0,
					   skb_frag_size(frag), DMA_TO_DEVICE);

		if (unlikely(dma_mapping_error(trans->dev, tb_phys)))
			return -EINVAL;
		trace_iwlwifi_dev_tx_tb(trans->dev, skb,
					skb_frag_address(frag),
					skb_frag_size(frag));
		tb_idx = iwl_pcie_txq_build_tfd(trans, txq, tb_phys,
						skb_frag_size(frag), false);
		if (tb_idx < 0)
			return tb_idx;

		out_meta->tbs |= BIT(tb_idx);
	}

	return 0;
}