#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  command; } ;
struct ide_cmd {scalar_t__ protocol; TYPE_2__ tf; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; TYPE_1__* tp_ops; } ;
typedef  TYPE_3__ ide_hwif_t ;
typedef  int /*<<< orphan*/  ide_handler_t ;
struct TYPE_11__ {int atapi_flags; TYPE_3__* hwif; } ;
typedef  TYPE_4__ ide_drive_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* exec_command ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ ATAPI_PROT_DMA ; 
 scalar_t__ ATAPI_PROT_PIO ; 
 int IDE_AFLAG_DRQ_INTERRUPT ; 
 int /*<<< orphan*/  __ide_set_handler (TYPE_4__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

void ide_execute_command(ide_drive_t *drive, struct ide_cmd *cmd,
			 ide_handler_t *handler, unsigned timeout)
{
	ide_hwif_t *hwif = drive->hwif;
	unsigned long flags;

	spin_lock_irqsave(&hwif->lock, flags);
	if ((cmd->protocol != ATAPI_PROT_DMA &&
	     cmd->protocol != ATAPI_PROT_PIO) ||
	    (drive->atapi_flags & IDE_AFLAG_DRQ_INTERRUPT))
		__ide_set_handler(drive, handler, timeout);
	hwif->tp_ops->exec_command(hwif, cmd->tf.command);
	/*
	 * Drive takes 400nS to respond, we must avoid the IRQ being
	 * serviced before that.
	 *
	 * FIXME: we could skip this delay with care on non shared devices
	 */
	ndelay(400);
	spin_unlock_irqrestore(&hwif->lock, flags);
}