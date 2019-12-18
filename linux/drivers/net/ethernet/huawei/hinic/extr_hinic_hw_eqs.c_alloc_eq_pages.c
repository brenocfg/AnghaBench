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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_hwif {struct pci_dev* pdev; } ;
struct hinic_eq {int num_pages; scalar_t__ type; int /*<<< orphan*/ * dma_addr; int /*<<< orphan*/ * virt_addr; int /*<<< orphan*/  page_size; int /*<<< orphan*/  wrapped; struct hinic_hwif* hwif; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EQ_HI_PHYS_ADDR_REG (struct hinic_eq*,int) ; 
 int /*<<< orphan*/  EQ_LO_PHYS_ADDR_REG (struct hinic_eq*,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HINIC_AEQ ; 
 scalar_t__ HINIC_CEQ ; 
 int /*<<< orphan*/  HINIC_EQ_ELEM_DESC_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRAPPED ; 
 int /*<<< orphan*/  aeq_elements_init (struct hinic_eq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceq_elements_init (struct hinic_eq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_hwif_write_reg (struct hinic_hwif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_eq_pages(struct hinic_eq *eq)
{
	struct hinic_hwif *hwif = eq->hwif;
	struct pci_dev *pdev = hwif->pdev;
	u32 init_val, addr, val;
	size_t addr_size;
	int err, pg;

	addr_size = eq->num_pages * sizeof(*eq->dma_addr);
	eq->dma_addr = devm_kzalloc(&pdev->dev, addr_size, GFP_KERNEL);
	if (!eq->dma_addr)
		return -ENOMEM;

	addr_size = eq->num_pages * sizeof(*eq->virt_addr);
	eq->virt_addr = devm_kzalloc(&pdev->dev, addr_size, GFP_KERNEL);
	if (!eq->virt_addr) {
		err = -ENOMEM;
		goto err_virt_addr_alloc;
	}

	for (pg = 0; pg < eq->num_pages; pg++) {
		eq->virt_addr[pg] = dma_alloc_coherent(&pdev->dev,
						       eq->page_size,
						       &eq->dma_addr[pg],
						       GFP_KERNEL);
		if (!eq->virt_addr[pg]) {
			err = -ENOMEM;
			goto err_dma_alloc;
		}

		addr = EQ_HI_PHYS_ADDR_REG(eq, pg);
		val = upper_32_bits(eq->dma_addr[pg]);

		hinic_hwif_write_reg(hwif, addr, val);

		addr = EQ_LO_PHYS_ADDR_REG(eq, pg);
		val = lower_32_bits(eq->dma_addr[pg]);

		hinic_hwif_write_reg(hwif, addr, val);
	}

	init_val = HINIC_EQ_ELEM_DESC_SET(eq->wrapped, WRAPPED);

	if (eq->type == HINIC_AEQ)
		aeq_elements_init(eq, init_val);
	else if (eq->type == HINIC_CEQ)
		ceq_elements_init(eq, init_val);

	return 0;

err_dma_alloc:
	while (--pg >= 0)
		dma_free_coherent(&pdev->dev, eq->page_size,
				  eq->virt_addr[pg],
				  eq->dma_addr[pg]);

	devm_kfree(&pdev->dev, eq->virt_addr);

err_virt_addr_alloc:
	devm_kfree(&pdev->dev, eq->dma_addr);
	return err;
}