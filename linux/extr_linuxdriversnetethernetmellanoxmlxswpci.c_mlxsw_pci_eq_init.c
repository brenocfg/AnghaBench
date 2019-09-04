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
struct mlxsw_pci_queue {int count; int /*<<< orphan*/  num; scalar_t__ consumer_counter; } ;
struct mlxsw_pci {int /*<<< orphan*/  core; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int MLXSW_PCI_AQ_PAGES ; 
 int /*<<< orphan*/  __mlxsw_pci_queue_page_get (struct mlxsw_pci_queue*,int) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_sw2hw_eq_int_msix_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_sw2hw_eq_log_eq_size_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_sw2hw_eq_pa_set (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_cmd_mbox_sw2hw_eq_st_set (char*,int) ; 
 int mlxsw_cmd_sw2hw_eq (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_pci_eqe_owner_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_pci_queue_doorbell_arm_consumer_ring (struct mlxsw_pci*,struct mlxsw_pci_queue*) ; 
 int /*<<< orphan*/  mlxsw_pci_queue_doorbell_consumer_ring (struct mlxsw_pci*,struct mlxsw_pci_queue*) ; 
 char* mlxsw_pci_queue_elem_get (struct mlxsw_pci_queue*,int) ; 

__attribute__((used)) static int mlxsw_pci_eq_init(struct mlxsw_pci *mlxsw_pci, char *mbox,
			     struct mlxsw_pci_queue *q)
{
	int i;
	int err;

	q->consumer_counter = 0;

	for (i = 0; i < q->count; i++) {
		char *elem = mlxsw_pci_queue_elem_get(q, i);

		mlxsw_pci_eqe_owner_set(elem, 1);
	}

	mlxsw_cmd_mbox_sw2hw_eq_int_msix_set(mbox, 1); /* MSI-X used */
	mlxsw_cmd_mbox_sw2hw_eq_st_set(mbox, 1); /* armed */
	mlxsw_cmd_mbox_sw2hw_eq_log_eq_size_set(mbox, ilog2(q->count));
	for (i = 0; i < MLXSW_PCI_AQ_PAGES; i++) {
		dma_addr_t mapaddr = __mlxsw_pci_queue_page_get(q, i);

		mlxsw_cmd_mbox_sw2hw_eq_pa_set(mbox, i, mapaddr);
	}
	err = mlxsw_cmd_sw2hw_eq(mlxsw_pci->core, mbox, q->num);
	if (err)
		return err;
	mlxsw_pci_queue_doorbell_consumer_ring(mlxsw_pci, q);
	mlxsw_pci_queue_doorbell_arm_consumer_ring(mlxsw_pci, q);
	return 0;
}