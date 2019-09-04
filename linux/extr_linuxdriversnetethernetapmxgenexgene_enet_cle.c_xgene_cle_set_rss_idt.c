#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct xgene_enet_pdata {int rxq_cnt; int /*<<< orphan*/  cle; TYPE_3__** rx_ring; } ;
struct TYPE_6__ {TYPE_2__* page_pool; TYPE_1__* buf_pool; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLE_CMD_WR ; 
 int /*<<< orphan*/  RSS_IDT ; 
 int XGENE_CLE_IDT_ENTRIES ; 
 int xgene_cle_dram_wr (int /*<<< orphan*/ *,size_t*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_cle_idt_to_hw (struct xgene_enet_pdata*,size_t,size_t,size_t,size_t*) ; 
 int xgene_cle_set_rss_skeys (int /*<<< orphan*/ *) ; 
 size_t xgene_enet_dst_ring_num (TYPE_3__*) ; 
 size_t xgene_enet_get_fpsel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_cle_set_rss_idt(struct xgene_enet_pdata *pdata)
{
	u32 fpsel, dstqid, nfpsel, idt_reg, idx;
	int i, ret = 0;
	u16 pool_id;

	for (i = 0; i < XGENE_CLE_IDT_ENTRIES; i++) {
		idx = i % pdata->rxq_cnt;
		pool_id = pdata->rx_ring[idx]->buf_pool->id;
		fpsel = xgene_enet_get_fpsel(pool_id);
		dstqid = xgene_enet_dst_ring_num(pdata->rx_ring[idx]);
		nfpsel = 0;
		if (pdata->rx_ring[idx]->page_pool) {
			pool_id = pdata->rx_ring[idx]->page_pool->id;
			nfpsel = xgene_enet_get_fpsel(pool_id);
		}

		idt_reg = 0;
		xgene_cle_idt_to_hw(pdata, dstqid, fpsel, nfpsel, &idt_reg);
		ret = xgene_cle_dram_wr(&pdata->cle, &idt_reg, 1, i,
					RSS_IDT, CLE_CMD_WR);
		if (ret)
			return ret;
	}

	ret = xgene_cle_set_rss_skeys(&pdata->cle);
	if (ret)
		return ret;

	return 0;
}