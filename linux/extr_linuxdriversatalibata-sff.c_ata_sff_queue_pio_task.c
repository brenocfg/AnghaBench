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
struct ata_port {int /*<<< orphan*/  sff_pio_task; struct ata_link* sff_pio_task_link; } ;
struct ata_link {struct ata_port* ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ata_sff_queue_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 

void ata_sff_queue_pio_task(struct ata_link *link, unsigned long delay)
{
	struct ata_port *ap = link->ap;

	WARN_ON((ap->sff_pio_task_link != NULL) &&
		(ap->sff_pio_task_link != link));
	ap->sff_pio_task_link = link;

	/* may fail if ata_sff_flush_pio_task() in progress */
	ata_sff_queue_delayed_work(&ap->sff_pio_task, msecs_to_jiffies(delay));
}