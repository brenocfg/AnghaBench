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
struct TYPE_4__ {int chunk_size; void* virt_addr; int /*<<< orphan*/  phy_addr; } ;
struct TYPE_3__ {int chunk_size; void* virt_addr; int /*<<< orphan*/  phy_addr; } ;
struct wcn36xx {TYPE_2__ data_mem_pool; int /*<<< orphan*/  dev; TYPE_1__ mgmt_mem_pool; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WCN36XX_BD_CHUNK_SIZE ; 
 size_t WCN36XX_DXE_CH_DESC_NUMB_TX_H ; 
 size_t WCN36XX_DXE_CH_DESC_NUMB_TX_L ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_dxe_free_mem_pools (struct wcn36xx*) ; 
 int /*<<< orphan*/  wcn36xx_err (char*) ; 

int wcn36xx_dxe_allocate_mem_pools(struct wcn36xx *wcn)
{
	size_t s;
	void *cpu_addr;

	/* Allocate BD headers for MGMT frames */

	/* Where this come from ask QC */
	wcn->mgmt_mem_pool.chunk_size =	WCN36XX_BD_CHUNK_SIZE +
		16 - (WCN36XX_BD_CHUNK_SIZE % 8);

	s = wcn->mgmt_mem_pool.chunk_size * WCN36XX_DXE_CH_DESC_NUMB_TX_H;
	cpu_addr = dma_alloc_coherent(wcn->dev, s,
				      &wcn->mgmt_mem_pool.phy_addr,
				      GFP_KERNEL);
	if (!cpu_addr)
		goto out_err;

	wcn->mgmt_mem_pool.virt_addr = cpu_addr;

	/* Allocate BD headers for DATA frames */

	/* Where this come from ask QC */
	wcn->data_mem_pool.chunk_size = WCN36XX_BD_CHUNK_SIZE +
		16 - (WCN36XX_BD_CHUNK_SIZE % 8);

	s = wcn->data_mem_pool.chunk_size * WCN36XX_DXE_CH_DESC_NUMB_TX_L;
	cpu_addr = dma_alloc_coherent(wcn->dev, s,
				      &wcn->data_mem_pool.phy_addr,
				      GFP_KERNEL);
	if (!cpu_addr)
		goto out_err;

	wcn->data_mem_pool.virt_addr = cpu_addr;

	return 0;

out_err:
	wcn36xx_dxe_free_mem_pools(wcn);
	wcn36xx_err("Failed to allocate BD mempool\n");
	return -ENOMEM;
}