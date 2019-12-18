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
struct Scsi_Host {int /*<<< orphan*/  work_q; TYPE_1__* hostt; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,int /*<<< orphan*/ ) ; 

void scsi_flush_work(struct Scsi_Host *shost)
{
	if (!shost->work_q) {
		shost_printk(KERN_ERR, shost,
			"ERROR: Scsi host '%s' attempted to flush scsi-work, "
			"when no workqueue created.\n", shost->hostt->name);
		dump_stack();
		return;
	}

	flush_workqueue(shost->work_q);
}