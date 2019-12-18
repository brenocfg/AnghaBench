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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {void* data; } ;
struct iwl_txq {int /*<<< orphan*/ * first_tb_bufs; int /*<<< orphan*/  write_ptr; } ;
struct iwl_trans {int /*<<< orphan*/  dev; } ;
struct iwl_tfh_tfd {int dummy; } ;
struct iwl_device_cmd {int /*<<< orphan*/  hdr; } ;
struct iwl_cmd_meta {int dummy; } ;
struct iwl_cmd_header {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int IWL_FIRST_TB_SIZE ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_pcie_gen2_set_tb (struct iwl_trans*,struct iwl_tfh_tfd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwl_pcie_gen2_tfd_unmap (struct iwl_trans*,struct iwl_cmd_meta*,struct iwl_tfh_tfd*) ; 
 scalar_t__ iwl_pcie_gen2_tx_add_frags (struct iwl_trans*,struct sk_buff*,struct iwl_tfh_tfd*,struct iwl_cmd_meta*) ; 
 int iwl_pcie_get_cmd_index (struct iwl_txq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_pcie_get_first_tb_dma (struct iwl_txq*,int) ; 
 struct iwl_tfh_tfd* iwl_pcie_get_tfd (struct iwl_trans*,struct iwl_txq*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct iwl_device_cmd*,int) ; 
 int skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  trace_iwlwifi_dev_tx (int /*<<< orphan*/ ,struct sk_buff*,struct iwl_tfh_tfd*,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  trace_iwlwifi_dev_tx_tb (int /*<<< orphan*/ ,struct sk_buff*,void*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct
iwl_tfh_tfd *iwl_pcie_gen2_build_tx(struct iwl_trans *trans,
				    struct iwl_txq *txq,
				    struct iwl_device_cmd *dev_cmd,
				    struct sk_buff *skb,
				    struct iwl_cmd_meta *out_meta,
				    int hdr_len,
				    int tx_cmd_len,
				    bool pad)
{
	int idx = iwl_pcie_get_cmd_index(txq, txq->write_ptr);
	struct iwl_tfh_tfd *tfd = iwl_pcie_get_tfd(trans, txq, idx);
	dma_addr_t tb_phys;
	int len, tb1_len, tb2_len;
	void *tb1_addr;

	tb_phys = iwl_pcie_get_first_tb_dma(txq, idx);

	/* The first TB points to bi-directional DMA data */
	memcpy(&txq->first_tb_bufs[idx], dev_cmd, IWL_FIRST_TB_SIZE);

	iwl_pcie_gen2_set_tb(trans, tfd, tb_phys, IWL_FIRST_TB_SIZE);

	/*
	 * The second TB (tb1) points to the remainder of the TX command
	 * and the 802.11 header - dword aligned size
	 * (This calculation modifies the TX command, so do it before the
	 * setup of the first TB)
	 */
	len = tx_cmd_len + sizeof(struct iwl_cmd_header) + hdr_len -
	      IWL_FIRST_TB_SIZE;

	if (pad)
		tb1_len = ALIGN(len, 4);
	else
		tb1_len = len;

	/* map the data for TB1 */
	tb1_addr = ((u8 *)&dev_cmd->hdr) + IWL_FIRST_TB_SIZE;
	tb_phys = dma_map_single(trans->dev, tb1_addr, tb1_len, DMA_TO_DEVICE);
	if (unlikely(dma_mapping_error(trans->dev, tb_phys)))
		goto out_err;
	iwl_pcie_gen2_set_tb(trans, tfd, tb_phys, tb1_len);
	trace_iwlwifi_dev_tx(trans->dev, skb, tfd, sizeof(*tfd), &dev_cmd->hdr,
			     IWL_FIRST_TB_SIZE + tb1_len, hdr_len);

	/* set up TFD's third entry to point to remainder of skb's head */
	tb2_len = skb_headlen(skb) - hdr_len;

	if (tb2_len > 0) {
		tb_phys = dma_map_single(trans->dev, skb->data + hdr_len,
					 tb2_len, DMA_TO_DEVICE);
		if (unlikely(dma_mapping_error(trans->dev, tb_phys)))
			goto out_err;
		iwl_pcie_gen2_set_tb(trans, tfd, tb_phys, tb2_len);
		trace_iwlwifi_dev_tx_tb(trans->dev, skb,
					skb->data + hdr_len,
					tb2_len);
	}

	if (iwl_pcie_gen2_tx_add_frags(trans, skb, tfd, out_meta))
		goto out_err;

	return tfd;

out_err:
	iwl_pcie_gen2_tfd_unmap(trans, out_meta, tfd);
	return NULL;
}