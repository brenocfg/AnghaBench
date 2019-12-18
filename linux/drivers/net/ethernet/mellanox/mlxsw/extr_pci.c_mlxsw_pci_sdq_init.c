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
struct mlxsw_pci_queue {int /*<<< orphan*/  num; scalar_t__ consumer_counter; scalar_t__ producer_counter; } ;
struct mlxsw_pci {int /*<<< orphan*/  core; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int MLXSW_PCI_AQ_PAGES ; 
 int /*<<< orphan*/  __mlxsw_pci_queue_page_get (struct mlxsw_pci_queue*,int) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_sw2hw_dq_cq_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_sw2hw_dq_log2_dq_sz_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_sw2hw_dq_pa_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_sw2hw_dq_sdq_tclass_set (char*,int) ; 
 int mlxsw_cmd_sw2hw_sdq (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_pci_queue_doorbell_producer_ring (struct mlxsw_pci*,struct mlxsw_pci_queue*) ; 

__attribute__((used)) static int mlxsw_pci_sdq_init(struct mlxsw_pci *mlxsw_pci, char *mbox,
			      struct mlxsw_pci_queue *q)
{
	int i;
	int err;

	q->producer_counter = 0;
	q->consumer_counter = 0;

	/* Set CQ of same number of this SDQ. */
	mlxsw_cmd_mbox_sw2hw_dq_cq_set(mbox, q->num);
	mlxsw_cmd_mbox_sw2hw_dq_sdq_tclass_set(mbox, 3);
	mlxsw_cmd_mbox_sw2hw_dq_log2_dq_sz_set(mbox, 3); /* 8 pages */
	for (i = 0; i < MLXSW_PCI_AQ_PAGES; i++) {
		dma_addr_t mapaddr = __mlxsw_pci_queue_page_get(q, i);

		mlxsw_cmd_mbox_sw2hw_dq_pa_set(mbox, i, mapaddr);
	}

	err = mlxsw_cmd_sw2hw_sdq(mlxsw_pci->core, mbox, q->num);
	if (err)
		return err;
	mlxsw_pci_queue_doorbell_producer_ring(mlxsw_pci, q);
	return 0;
}