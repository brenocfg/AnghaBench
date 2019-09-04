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
struct qed_chain {int /*<<< orphan*/  p_phys_addr; int /*<<< orphan*/  p_virt_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QED_CHAIN_PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_chain_free_single(struct qed_dev *cdev,
				  struct qed_chain *p_chain)
{
	if (!p_chain->p_virt_addr)
		return;

	dma_free_coherent(&cdev->pdev->dev,
			  QED_CHAIN_PAGE_SIZE,
			  p_chain->p_virt_addr, p_chain->p_phys_addr);
}