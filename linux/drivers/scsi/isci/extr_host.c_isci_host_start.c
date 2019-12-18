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
struct isci_host {int /*<<< orphan*/  scic_lock; int /*<<< orphan*/  flags; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {struct isci_host* lldd_ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  IHOST_START_PENDING ; 
 TYPE_1__* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  sci_controller_enable_interrupts (struct isci_host*) ; 
 unsigned long sci_controller_get_suggested_start_timeout (struct isci_host*) ; 
 int /*<<< orphan*/  sci_controller_start (struct isci_host*,unsigned long) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void isci_host_start(struct Scsi_Host *shost)
{
	struct isci_host *ihost = SHOST_TO_SAS_HA(shost)->lldd_ha;
	unsigned long tmo = sci_controller_get_suggested_start_timeout(ihost);

	set_bit(IHOST_START_PENDING, &ihost->flags);

	spin_lock_irq(&ihost->scic_lock);
	sci_controller_start(ihost, tmo);
	sci_controller_enable_interrupts(ihost);
	spin_unlock_irq(&ihost->scic_lock);
}