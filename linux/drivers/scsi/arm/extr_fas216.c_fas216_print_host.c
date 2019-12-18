#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  irq; int /*<<< orphan*/  io_base; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_1__ scsi; } ;
typedef  TYPE_2__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fas216_print_host(FAS216_Info *info, struct seq_file *m)
{
	seq_printf(m,
			"\n"
			"Chip    : %s\n"
			" Address: 0x%p\n"
			" IRQ    : %d\n"
			" DMA    : %d\n",
			info->scsi.type, info->scsi.io_base,
			info->scsi.irq, info->scsi.dma);
}