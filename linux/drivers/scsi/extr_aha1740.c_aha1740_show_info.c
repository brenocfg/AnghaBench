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
struct seq_file {int dummy; } ;
struct aha1740_hostdata {scalar_t__ translation; TYPE_1__* edev; } ;
struct Scsi_Host {int /*<<< orphan*/  irq; int /*<<< orphan*/  io_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  slot; } ;

/* Variables and functions */
 struct aha1740_hostdata* HOSTDATA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int aha1740_show_info(struct seq_file *m, struct Scsi_Host *shpnt)
{
	struct aha1740_hostdata *host = HOSTDATA(shpnt);
	seq_printf(m, "aha174x at IO:%lx, IRQ %d, SLOT %d.\n"
		      "Extended translation %sabled.\n",
		      shpnt->io_port, shpnt->irq, host->edev->slot,
		      host->translation ? "en" : "dis");
	return 0;
}