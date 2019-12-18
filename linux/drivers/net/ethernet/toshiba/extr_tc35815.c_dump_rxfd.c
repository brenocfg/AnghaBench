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
struct TYPE_3__ {int /*<<< orphan*/  FDCtl; int /*<<< orphan*/  FDStat; int /*<<< orphan*/  FDSystem; int /*<<< orphan*/  FDNext; } ;
struct RxFD {TYPE_2__* bd; TYPE_1__ fd; } ;
struct TYPE_4__ {int /*<<< orphan*/  BDCtl; int /*<<< orphan*/  BuffData; } ;

/* Variables and functions */
 int FD_BDCnt_MASK ; 
 int FD_BDCnt_SHIFT ; 
 int FD_CownsFD ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int
dump_rxfd(struct RxFD *fd)
{
	int i, bd_count = (le32_to_cpu(fd->fd.FDCtl) & FD_BDCnt_MASK) >> FD_BDCnt_SHIFT;
	if (bd_count > 8)
		bd_count = 8;
	printk("RxFD(%p): %08x %08x %08x %08x\n", fd,
	       le32_to_cpu(fd->fd.FDNext),
	       le32_to_cpu(fd->fd.FDSystem),
	       le32_to_cpu(fd->fd.FDStat),
	       le32_to_cpu(fd->fd.FDCtl));
	if (le32_to_cpu(fd->fd.FDCtl) & FD_CownsFD)
		return 0;
	printk("BD: ");
	for (i = 0; i < bd_count; i++)
		printk(" %08x %08x",
		       le32_to_cpu(fd->bd[i].BuffData),
		       le32_to_cpu(fd->bd[i].BDCtl));
	printk("\n");
	return bd_count;
}