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
struct TYPE_4__ {int /*<<< orphan*/  pci_int_reg; int /*<<< orphan*/  tgt_mask_reg; int /*<<< orphan*/  tgt_status_reg; int /*<<< orphan*/  int_vec_bit; } ;
struct qla_hw_data {int qdr_sn_window; int ddr_mn_window; int curr_window; size_t portnum; TYPE_2__ nx_legacy_intr; TYPE_1__* pdev; int /*<<< orphan*/  hw_lock; } ;
struct qla82xx_legacy_intr_set {int /*<<< orphan*/  pci_int_reg; int /*<<< orphan*/  tgt_mask_reg; int /*<<< orphan*/  tgt_status_reg; int /*<<< orphan*/  int_vec_bit; } ;
struct TYPE_3__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 size_t PCI_FUNC (int /*<<< orphan*/ ) ; 
 struct qla82xx_legacy_intr_set* legacy_intr ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

void qla82xx_init_flags(struct qla_hw_data *ha)
{
	struct qla82xx_legacy_intr_set *nx_legacy_intr;

	/* ISP 8021 initializations */
	rwlock_init(&ha->hw_lock);
	ha->qdr_sn_window = -1;
	ha->ddr_mn_window = -1;
	ha->curr_window = 255;
	ha->portnum = PCI_FUNC(ha->pdev->devfn);
	nx_legacy_intr = &legacy_intr[ha->portnum];
	ha->nx_legacy_intr.int_vec_bit = nx_legacy_intr->int_vec_bit;
	ha->nx_legacy_intr.tgt_status_reg = nx_legacy_intr->tgt_status_reg;
	ha->nx_legacy_intr.tgt_mask_reg = nx_legacy_intr->tgt_mask_reg;
	ha->nx_legacy_intr.pci_int_reg = nx_legacy_intr->pci_int_reg;
}