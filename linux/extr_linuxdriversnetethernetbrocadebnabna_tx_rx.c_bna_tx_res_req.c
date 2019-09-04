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
typedef  int u32 ;
struct bna_tcb {int dummy; } ;
struct TYPE_3__ {int num; int /*<<< orphan*/  intr_type; } ;
struct bna_mem_info {int len; int num; void* mem_type; } ;
struct TYPE_4__ {TYPE_1__ intr_info; struct bna_mem_info mem_info; } ;
struct bna_res_info {TYPE_2__ res_u; void* res_type; } ;
struct bna_dma_addr {int dummy; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int BFI_IBIDX_SIZE ; 
 int BFI_TXQ_WI_SIZE ; 
 int /*<<< orphan*/  BNA_INTR_T_MSIX ; 
 void* BNA_MEM_T_DMA ; 
 void* BNA_MEM_T_KVA ; 
 void* BNA_RES_T_INTR ; 
 void* BNA_RES_T_MEM ; 
 size_t BNA_TX_RES_INTR_T_TXCMPL ; 
 size_t BNA_TX_RES_MEM_T_IBIDX ; 
 size_t BNA_TX_RES_MEM_T_PAGE ; 
 size_t BNA_TX_RES_MEM_T_QPT ; 
 size_t BNA_TX_RES_MEM_T_SWQPT ; 
 size_t BNA_TX_RES_MEM_T_TCB ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 

void
bna_tx_res_req(int num_txq, int txq_depth, struct bna_res_info *res_info)
{
	u32 q_size;
	u32 page_count;
	struct bna_mem_info *mem_info;

	res_info[BNA_TX_RES_MEM_T_TCB].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_TX_RES_MEM_T_TCB].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = sizeof(struct bna_tcb);
	mem_info->num = num_txq;

	q_size = txq_depth * BFI_TXQ_WI_SIZE;
	q_size = ALIGN(q_size, PAGE_SIZE);
	page_count = q_size >> PAGE_SHIFT;

	res_info[BNA_TX_RES_MEM_T_QPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_TX_RES_MEM_T_QPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = page_count * sizeof(struct bna_dma_addr);
	mem_info->num = num_txq;

	res_info[BNA_TX_RES_MEM_T_SWQPT].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_TX_RES_MEM_T_SWQPT].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_KVA;
	mem_info->len = page_count * sizeof(void *);
	mem_info->num = num_txq;

	res_info[BNA_TX_RES_MEM_T_PAGE].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_TX_RES_MEM_T_PAGE].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = PAGE_SIZE * page_count;
	mem_info->num = num_txq;

	res_info[BNA_TX_RES_MEM_T_IBIDX].res_type = BNA_RES_T_MEM;
	mem_info = &res_info[BNA_TX_RES_MEM_T_IBIDX].res_u.mem_info;
	mem_info->mem_type = BNA_MEM_T_DMA;
	mem_info->len = BFI_IBIDX_SIZE;
	mem_info->num = num_txq;

	res_info[BNA_TX_RES_INTR_T_TXCMPL].res_type = BNA_RES_T_INTR;
	res_info[BNA_TX_RES_INTR_T_TXCMPL].res_u.intr_info.intr_type =
			BNA_INTR_T_MSIX;
	res_info[BNA_TX_RES_INTR_T_TXCMPL].res_u.intr_info.num = num_txq;
}