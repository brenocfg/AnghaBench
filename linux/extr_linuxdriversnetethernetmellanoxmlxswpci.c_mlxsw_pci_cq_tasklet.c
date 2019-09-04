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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  comp_rdq_count; int /*<<< orphan*/  v; int /*<<< orphan*/  comp_sdq_count; } ;
struct TYPE_4__ {TYPE_1__ cq; } ;
struct mlxsw_pci_queue {int count; TYPE_2__ u; int /*<<< orphan*/  elem_size; struct mlxsw_pci* pci; } ;
struct mlxsw_pci {int dummy; } ;

/* Variables and functions */
 int MLXSW_PCI_CQE_SIZE_MAX ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 char* mlxsw_pci_cq_sw_cqe_get (struct mlxsw_pci_queue*) ; 
 scalar_t__ mlxsw_pci_cqe_dqn_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_pci_cqe_rdq_handle (struct mlxsw_pci*,struct mlxsw_pci_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_pci_cqe_sdq_handle (struct mlxsw_pci*,struct mlxsw_pci_queue*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mlxsw_pci_cqe_sr_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_pci_cqe_wqe_counter_get (char*) ; 
 int /*<<< orphan*/  mlxsw_pci_queue_doorbell_arm_consumer_ring (struct mlxsw_pci*,struct mlxsw_pci_queue*) ; 
 int /*<<< orphan*/  mlxsw_pci_queue_doorbell_consumer_ring (struct mlxsw_pci*,struct mlxsw_pci_queue*) ; 
 struct mlxsw_pci_queue* mlxsw_pci_rdq_get (struct mlxsw_pci*,scalar_t__) ; 
 struct mlxsw_pci_queue* mlxsw_pci_sdq_get (struct mlxsw_pci*,scalar_t__) ; 

__attribute__((used)) static void mlxsw_pci_cq_tasklet(unsigned long data)
{
	struct mlxsw_pci_queue *q = (struct mlxsw_pci_queue *) data;
	struct mlxsw_pci *mlxsw_pci = q->pci;
	char *cqe;
	int items = 0;
	int credits = q->count >> 1;

	while ((cqe = mlxsw_pci_cq_sw_cqe_get(q))) {
		u16 wqe_counter = mlxsw_pci_cqe_wqe_counter_get(cqe);
		u8 sendq = mlxsw_pci_cqe_sr_get(q->u.cq.v, cqe);
		u8 dqn = mlxsw_pci_cqe_dqn_get(q->u.cq.v, cqe);
		char ncqe[MLXSW_PCI_CQE_SIZE_MAX];

		memcpy(ncqe, cqe, q->elem_size);
		mlxsw_pci_queue_doorbell_consumer_ring(mlxsw_pci, q);

		if (sendq) {
			struct mlxsw_pci_queue *sdq;

			sdq = mlxsw_pci_sdq_get(mlxsw_pci, dqn);
			mlxsw_pci_cqe_sdq_handle(mlxsw_pci, sdq,
						 wqe_counter, ncqe);
			q->u.cq.comp_sdq_count++;
		} else {
			struct mlxsw_pci_queue *rdq;

			rdq = mlxsw_pci_rdq_get(mlxsw_pci, dqn);
			mlxsw_pci_cqe_rdq_handle(mlxsw_pci, rdq,
						 wqe_counter, q->u.cq.v, ncqe);
			q->u.cq.comp_rdq_count++;
		}
		if (++items == credits)
			break;
	}
	if (items)
		mlxsw_pci_queue_doorbell_arm_consumer_ring(mlxsw_pci, q);
}