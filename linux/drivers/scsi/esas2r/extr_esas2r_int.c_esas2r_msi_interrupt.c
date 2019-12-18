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
typedef  scalar_t__ u32 ;
struct esas2r_adapter {int /*<<< orphan*/  disable_cnt; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  MU_DOORBELL_OUT ; 
 scalar_t__ MU_INTSTAT_DRBL ; 
 scalar_t__ MU_INTSTAT_POST_OUT ; 
 int /*<<< orphan*/  MU_INT_STATUS_OUT ; 
 int /*<<< orphan*/  MU_OLIS_INT ; 
 int /*<<< orphan*/  MU_OUT_LIST_INT_STAT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_disable_chip_interrupts (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_do_deferred_processes (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_do_tasklet_tasks (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_doorbell_interrupt (struct esas2r_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  esas2r_enable_chip_interrupts (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_flush_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_get_outbound_responses (struct esas2r_adapter*) ; 
 scalar_t__ esas2r_read_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_write_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (scalar_t__) ; 

irqreturn_t esas2r_msi_interrupt(int irq, void *dev_id)
{
	struct esas2r_adapter *a = (struct esas2r_adapter *)dev_id;
	u32 intstat;
	u32 doorbell;

	intstat = esas2r_read_register_dword(a, MU_INT_STATUS_OUT);

	if (likely(intstat & MU_INTSTAT_POST_OUT)) {
		/* clear the interrupt */

		esas2r_write_register_dword(a, MU_OUT_LIST_INT_STAT,
					    MU_OLIS_INT);
		esas2r_flush_register_dword(a, MU_OUT_LIST_INT_STAT);

		esas2r_get_outbound_responses(a);
	}

	if (unlikely(intstat & MU_INTSTAT_DRBL)) {
		doorbell = esas2r_read_register_dword(a, MU_DOORBELL_OUT);
		if (doorbell != 0)
			esas2r_doorbell_interrupt(a, doorbell);
	}

	/*
	 * Work around a chip bug and force a new MSI to be sent if one is
	 * still pending.
	 */
	esas2r_disable_chip_interrupts(a);
	esas2r_enable_chip_interrupts(a);

	if (likely(atomic_read(&a->disable_cnt) == 0))
		esas2r_do_deferred_processes(a);

	esas2r_do_tasklet_tasks(a);

	return 1;
}