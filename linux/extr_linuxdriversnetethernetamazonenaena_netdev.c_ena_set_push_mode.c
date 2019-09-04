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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ max_llq_num; } ;
struct ena_com_dev_get_features_ctx {TYPE_1__ max_queues; } ;
struct ena_com_dev {int /*<<< orphan*/  tx_mem_queue_type; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENA_ADMIN_PLACEMENT_POLICY_DEV ; 
 int /*<<< orphan*/  ENA_ADMIN_PLACEMENT_POLICY_HOST ; 
 int /*<<< orphan*/  ENA_MEM_BAR ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int pci_select_bars (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_set_push_mode(struct pci_dev *pdev, struct ena_com_dev *ena_dev,
			      struct ena_com_dev_get_features_ctx *get_feat_ctx)
{
	bool has_mem_bar;

	has_mem_bar = pci_select_bars(pdev, IORESOURCE_MEM) & BIT(ENA_MEM_BAR);

	/* Enable push mode if device supports LLQ */
	if (has_mem_bar && (get_feat_ctx->max_queues.max_llq_num > 0))
		ena_dev->tx_mem_queue_type = ENA_ADMIN_PLACEMENT_POLICY_DEV;
	else
		ena_dev->tx_mem_queue_type = ENA_ADMIN_PLACEMENT_POLICY_HOST;
}