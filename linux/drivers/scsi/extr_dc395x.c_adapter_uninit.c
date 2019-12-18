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
struct AdapterCtlBlk {int /*<<< orphan*/  io_port_len; scalar_t__ io_port_base; scalar_t__ irq_level; int /*<<< orphan*/  scsi_host; int /*<<< orphan*/  selto_timer; int /*<<< orphan*/  waiting_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC395x_LOCK_IO (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  DC395x_UNLOCK_IO (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  adapter_remove_and_free_all_devices (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  adapter_sg_tables_free (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  adapter_uninit_chip (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adapter_uninit(struct AdapterCtlBlk *acb)
{
	unsigned long flags;
	DC395x_LOCK_IO(acb->scsi_host, flags);

	/* remove timers */
	if (timer_pending(&acb->waiting_timer))
		del_timer(&acb->waiting_timer);
	if (timer_pending(&acb->selto_timer))
		del_timer(&acb->selto_timer);

	adapter_uninit_chip(acb);
	adapter_remove_and_free_all_devices(acb);
	DC395x_UNLOCK_IO(acb->scsi_host, flags);

	if (acb->irq_level)
		free_irq(acb->irq_level, acb);
	if (acb->io_port_base)
		release_region(acb->io_port_base, acb->io_port_len);

	adapter_sg_tables_free(acb);
}