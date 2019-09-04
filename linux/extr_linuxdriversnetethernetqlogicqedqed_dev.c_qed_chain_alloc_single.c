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
struct qed_dev {TYPE_1__* pdev; } ;
struct qed_chain {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QED_CHAIN_PAGE_SIZE ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_chain_init_mem (struct qed_chain*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_chain_reset (struct qed_chain*) ; 

__attribute__((used)) static int
qed_chain_alloc_single(struct qed_dev *cdev, struct qed_chain *p_chain)
{
	dma_addr_t p_phys = 0;
	void *p_virt = NULL;

	p_virt = dma_alloc_coherent(&cdev->pdev->dev,
				    QED_CHAIN_PAGE_SIZE, &p_phys, GFP_KERNEL);
	if (!p_virt)
		return -ENOMEM;

	qed_chain_init_mem(p_chain, p_virt, p_phys);
	qed_chain_reset(p_chain);

	return 0;
}