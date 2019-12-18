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
struct bd_list {int num_tabs; int num_bds_table; struct bd_table** bd_table_array; int /*<<< orphan*/  hwd_bdi; int /*<<< orphan*/  eqp_bdi; int /*<<< orphan*/  max_bdi; } ;
struct bdc_ep {int /*<<< orphan*/  ep_num; int /*<<< orphan*/  name; struct bd_list bd_list; } ;
struct bdc_bd {int /*<<< orphan*/ * offset; } ;
struct bdc {int /*<<< orphan*/  dev; } ;
struct bd_table {scalar_t__ dma; struct bdc_bd* start_bd; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

void bdc_dbg_bd_list(struct bdc *bdc, struct bdc_ep *ep)
{
	struct bd_list *bd_list = &ep->bd_list;
	struct bd_table *bd_table;
	struct bdc_bd *bd;
	int tbi, bdi, gbdi;
	dma_addr_t dma;

	gbdi = 0;
	dev_vdbg(bdc->dev,
		"Dump bd list for %s epnum:%d\n",
		ep->name, ep->ep_num);

	dev_vdbg(bdc->dev,
		"tabs:%d max_bdi:%d eqp_bdi:%d hwd_bdi:%d num_bds_table:%d\n",
		bd_list->num_tabs, bd_list->max_bdi, bd_list->eqp_bdi,
		bd_list->hwd_bdi, bd_list->num_bds_table);

	for (tbi = 0; tbi < bd_list->num_tabs; tbi++) {
		bd_table = bd_list->bd_table_array[tbi];
		for (bdi = 0; bdi < bd_list->num_bds_table; bdi++) {
			bd =  bd_table->start_bd + bdi;
			dma = bd_table->dma + (sizeof(struct bdc_bd) * bdi);
			dev_vdbg(bdc->dev,
				"tbi:%2d bdi:%2d gbdi:%2d virt:%p phys:%llx %08x %08x %08x %08x\n",
				tbi, bdi, gbdi++, bd, (unsigned long long)dma,
				le32_to_cpu(bd->offset[0]),
				le32_to_cpu(bd->offset[1]),
				le32_to_cpu(bd->offset[2]),
				le32_to_cpu(bd->offset[3]));
		}
		dev_vdbg(bdc->dev, "\n\n");
	}
}