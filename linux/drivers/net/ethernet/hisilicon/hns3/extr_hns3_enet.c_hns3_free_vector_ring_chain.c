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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hns3_enet_tqp_vector {TYPE_1__* handle; } ;
struct hnae3_ring_chain_node {struct hnae3_ring_chain_node* next; } ;
struct TYPE_2__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,struct hnae3_ring_chain_node*) ; 

__attribute__((used)) static void hns3_free_vector_ring_chain(struct hns3_enet_tqp_vector *tqp_vector,
					struct hnae3_ring_chain_node *head)
{
	struct pci_dev *pdev = tqp_vector->handle->pdev;
	struct hnae3_ring_chain_node *chain_tmp, *chain;

	chain = head->next;

	while (chain) {
		chain_tmp = chain->next;
		devm_kfree(&pdev->dev, chain);
		chain = chain_tmp;
	}
}