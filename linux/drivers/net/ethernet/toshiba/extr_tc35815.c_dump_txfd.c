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
struct TYPE_4__ {int /*<<< orphan*/  BDCtl; int /*<<< orphan*/  BuffData; } ;
struct TYPE_3__ {int /*<<< orphan*/  FDCtl; int /*<<< orphan*/  FDStat; int /*<<< orphan*/  FDSystem; int /*<<< orphan*/  FDNext; } ;
struct TxFD {TYPE_2__ bd; TYPE_1__ fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void
dump_txfd(struct TxFD *fd)
{
	printk("TxFD(%p): %08x %08x %08x %08x\n", fd,
	       le32_to_cpu(fd->fd.FDNext),
	       le32_to_cpu(fd->fd.FDSystem),
	       le32_to_cpu(fd->fd.FDStat),
	       le32_to_cpu(fd->fd.FDCtl));
	printk("BD: ");
	printk(" %08x %08x",
	       le32_to_cpu(fd->bd.BuffData),
	       le32_to_cpu(fd->bd.BDCtl));
	printk("\n");
}