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
typedef  int /*<<< orphan*/  u32 ;
struct netxen_legacy_intr_set {int /*<<< orphan*/  pci_int_reg; int /*<<< orphan*/  tgt_mask_reg; int /*<<< orphan*/  int_vec_bit; int /*<<< orphan*/  tgt_status_reg; } ;
struct TYPE_2__ {scalar_t__ revision_id; size_t pci_func; } ;
struct netxen_adapter {void* crb_int_state_reg; TYPE_1__ ahw; void* isr_int_vec; void* pci_int_reg; void* tgt_mask_reg; void* tgt_status_reg; int /*<<< orphan*/  int_vec_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_INT_VECTOR ; 
 int /*<<< orphan*/  ISR_INT_STATE_REG ; 
 int /*<<< orphan*/  ISR_INT_VECTOR ; 
 scalar_t__ NX_P3_B0 ; 
 scalar_t__ NX_P3_B1 ; 
 struct netxen_legacy_intr_set* legacy_intr ; 
 void* netxen_get_ioaddr (struct netxen_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
netxen_initialize_interrupt_registers(struct netxen_adapter *adapter)
{
	struct netxen_legacy_intr_set *legacy_intrp;
	u32 tgt_status_reg, int_state_reg;

	if (adapter->ahw.revision_id >= NX_P3_B0)
		legacy_intrp = &legacy_intr[adapter->ahw.pci_func];
	else
		legacy_intrp = &legacy_intr[0];

	tgt_status_reg = legacy_intrp->tgt_status_reg;
	int_state_reg = ISR_INT_STATE_REG;

	adapter->int_vec_bit = legacy_intrp->int_vec_bit;
	adapter->tgt_status_reg = netxen_get_ioaddr(adapter, tgt_status_reg);
	adapter->tgt_mask_reg = netxen_get_ioaddr(adapter,
						  legacy_intrp->tgt_mask_reg);
	adapter->pci_int_reg = netxen_get_ioaddr(adapter,
						 legacy_intrp->pci_int_reg);
	adapter->isr_int_vec = netxen_get_ioaddr(adapter, ISR_INT_VECTOR);

	if (adapter->ahw.revision_id >= NX_P3_B1)
		adapter->crb_int_state_reg = netxen_get_ioaddr(adapter,
							       int_state_reg);
	else
		adapter->crb_int_state_reg = netxen_get_ioaddr(adapter,
							       CRB_INT_VECTOR);
}