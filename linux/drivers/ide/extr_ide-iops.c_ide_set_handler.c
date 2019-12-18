#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ ide_hwif_t ;
typedef  int /*<<< orphan*/  ide_handler_t ;
struct TYPE_6__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  __ide_set_handler (TYPE_2__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ide_set_handler(ide_drive_t *drive, ide_handler_t *handler,
		     unsigned int timeout)
{
	ide_hwif_t *hwif = drive->hwif;
	unsigned long flags;

	spin_lock_irqsave(&hwif->lock, flags);
	__ide_set_handler(drive, handler, timeout);
	spin_unlock_irqrestore(&hwif->lock, flags);
}