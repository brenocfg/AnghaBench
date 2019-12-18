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
struct ucc_geth_private {int /*<<< orphan*/ * ug_regs; int /*<<< orphan*/  ind_hash_q; int /*<<< orphan*/  group_hash_q; TYPE_2__* p_init_enet_param_shadow; TYPE_1__* ug_info; int /*<<< orphan*/ * p_rx_bd_qs_tbl; int /*<<< orphan*/  rx_bd_qs_tbl_offset; int /*<<< orphan*/ * p_rx_irq_coalescing_tbl; int /*<<< orphan*/  rx_irq_coalescing_tbl_offset; int /*<<< orphan*/ * p_rx_fw_statistics_pram; int /*<<< orphan*/  rx_fw_statistics_pram_offset; int /*<<< orphan*/ * p_tx_fw_statistics_pram; int /*<<< orphan*/  tx_fw_statistics_pram_offset; int /*<<< orphan*/ * p_scheduler; int /*<<< orphan*/  scheduler_offset; int /*<<< orphan*/ * p_send_q_mem_reg; int /*<<< orphan*/  send_q_mem_reg_offset; int /*<<< orphan*/ * p_tx_glbl_pram; int /*<<< orphan*/  tx_glbl_pram_offset; int /*<<< orphan*/ * p_rx_glbl_pram; int /*<<< orphan*/  rx_glbl_pram_offset; int /*<<< orphan*/ * p_exf_glbl_param; int /*<<< orphan*/  exf_glbl_param_offset; int /*<<< orphan*/ * p_thread_data_rx; int /*<<< orphan*/  thread_dat_rx_offset; int /*<<< orphan*/ * p_thread_data_tx; int /*<<< orphan*/  thread_dat_tx_offset; int /*<<< orphan*/ * uccf; } ;
struct TYPE_4__ {int /*<<< orphan*/ * txthread; int /*<<< orphan*/ * rxthread; } ;
struct TYPE_3__ {int /*<<< orphan*/  riscTx; int /*<<< orphan*/  riscRx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_ADDR_CONT_ENTRY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENET_INIT_PARAM_MAX_ENTRIES_RX ; 
 int /*<<< orphan*/  ENET_INIT_PARAM_MAX_ENTRIES_TX ; 
 int /*<<< orphan*/  dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_enet_addr_container (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qe_muram_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_init_enet_entries (struct ucc_geth_private*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ucc_fast_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucc_geth_free_rx (struct ucc_geth_private*) ; 
 int /*<<< orphan*/  ucc_geth_free_tx (struct ucc_geth_private*) ; 

__attribute__((used)) static void ucc_geth_memclean(struct ucc_geth_private *ugeth)
{
	if (!ugeth)
		return;

	if (ugeth->uccf) {
		ucc_fast_free(ugeth->uccf);
		ugeth->uccf = NULL;
	}

	if (ugeth->p_thread_data_tx) {
		qe_muram_free(ugeth->thread_dat_tx_offset);
		ugeth->p_thread_data_tx = NULL;
	}
	if (ugeth->p_thread_data_rx) {
		qe_muram_free(ugeth->thread_dat_rx_offset);
		ugeth->p_thread_data_rx = NULL;
	}
	if (ugeth->p_exf_glbl_param) {
		qe_muram_free(ugeth->exf_glbl_param_offset);
		ugeth->p_exf_glbl_param = NULL;
	}
	if (ugeth->p_rx_glbl_pram) {
		qe_muram_free(ugeth->rx_glbl_pram_offset);
		ugeth->p_rx_glbl_pram = NULL;
	}
	if (ugeth->p_tx_glbl_pram) {
		qe_muram_free(ugeth->tx_glbl_pram_offset);
		ugeth->p_tx_glbl_pram = NULL;
	}
	if (ugeth->p_send_q_mem_reg) {
		qe_muram_free(ugeth->send_q_mem_reg_offset);
		ugeth->p_send_q_mem_reg = NULL;
	}
	if (ugeth->p_scheduler) {
		qe_muram_free(ugeth->scheduler_offset);
		ugeth->p_scheduler = NULL;
	}
	if (ugeth->p_tx_fw_statistics_pram) {
		qe_muram_free(ugeth->tx_fw_statistics_pram_offset);
		ugeth->p_tx_fw_statistics_pram = NULL;
	}
	if (ugeth->p_rx_fw_statistics_pram) {
		qe_muram_free(ugeth->rx_fw_statistics_pram_offset);
		ugeth->p_rx_fw_statistics_pram = NULL;
	}
	if (ugeth->p_rx_irq_coalescing_tbl) {
		qe_muram_free(ugeth->rx_irq_coalescing_tbl_offset);
		ugeth->p_rx_irq_coalescing_tbl = NULL;
	}
	if (ugeth->p_rx_bd_qs_tbl) {
		qe_muram_free(ugeth->rx_bd_qs_tbl_offset);
		ugeth->p_rx_bd_qs_tbl = NULL;
	}
	if (ugeth->p_init_enet_param_shadow) {
		return_init_enet_entries(ugeth,
					 &(ugeth->p_init_enet_param_shadow->
					   rxthread[0]),
					 ENET_INIT_PARAM_MAX_ENTRIES_RX,
					 ugeth->ug_info->riscRx, 1);
		return_init_enet_entries(ugeth,
					 &(ugeth->p_init_enet_param_shadow->
					   txthread[0]),
					 ENET_INIT_PARAM_MAX_ENTRIES_TX,
					 ugeth->ug_info->riscTx, 0);
		kfree(ugeth->p_init_enet_param_shadow);
		ugeth->p_init_enet_param_shadow = NULL;
	}
	ucc_geth_free_tx(ugeth);
	ucc_geth_free_rx(ugeth);
	while (!list_empty(&ugeth->group_hash_q))
		put_enet_addr_container(ENET_ADDR_CONT_ENTRY
					(dequeue(&ugeth->group_hash_q)));
	while (!list_empty(&ugeth->ind_hash_q))
		put_enet_addr_container(ENET_ADDR_CONT_ENTRY
					(dequeue(&ugeth->ind_hash_q)));
	if (ugeth->ug_regs) {
		iounmap(ugeth->ug_regs);
		ugeth->ug_regs = NULL;
	}
}