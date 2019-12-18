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
struct tape_device {int /*<<< orphan*/  cdev_id; } ;
struct TYPE_3__ {int dstat; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct irb {TYPE_2__ scsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*,...) ; 
 int TAPE_IO_SUCCESS ; 
 int /*<<< orphan*/  TO_MSEN ; 
 int /*<<< orphan*/  tape_34xx_delete_sbid_from (struct tape_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_34xx_schedule_work (struct tape_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_dump_sense_dbf (struct tape_device*,int /*<<< orphan*/ *,struct irb*) ; 

__attribute__((used)) static int
tape_34xx_unsolicited_irq(struct tape_device *device, struct irb *irb)
{
	if (irb->scsw.cmd.dstat == 0x85) { /* READY */
		/* A medium was inserted in the drive. */
		DBF_EVENT(6, "xuud med\n");
		tape_34xx_delete_sbid_from(device, 0);
		tape_34xx_schedule_work(device, TO_MSEN);
	} else {
		DBF_EVENT(3, "unsol.irq! dev end: %08x\n", device->cdev_id);
		tape_dump_sense_dbf(device, NULL, irb);
	}
	return TAPE_IO_SUCCESS;
}