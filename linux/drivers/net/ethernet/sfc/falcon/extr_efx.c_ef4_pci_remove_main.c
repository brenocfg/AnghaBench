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
struct ef4_nic {scalar_t__ state; TYPE_1__* type; int /*<<< orphan*/  reset_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fini ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ STATE_READY ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ef4_disable_interrupts (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_fini_napi (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_fini_port (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_nic_fini_interrupt (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_remove_all (struct ef4_nic*) ; 
 int /*<<< orphan*/  stub1 (struct ef4_nic*) ; 

__attribute__((used)) static void ef4_pci_remove_main(struct ef4_nic *efx)
{
	/* Flush reset_work. It can no longer be scheduled since we
	 * are not READY.
	 */
	BUG_ON(efx->state == STATE_READY);
	cancel_work_sync(&efx->reset_work);

	ef4_disable_interrupts(efx);
	ef4_nic_fini_interrupt(efx);
	ef4_fini_port(efx);
	efx->type->fini(efx);
	ef4_fini_napi(efx);
	ef4_remove_all(efx);
}