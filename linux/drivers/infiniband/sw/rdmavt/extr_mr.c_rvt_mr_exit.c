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
struct TYPE_2__ {int /*<<< orphan*/  table; } ;
struct rvt_dev_info {TYPE_1__ lkey_table; scalar_t__ dma_mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  rvt_pr_err (struct rvt_dev_info*,char*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void rvt_mr_exit(struct rvt_dev_info *rdi)
{
	if (rdi->dma_mr)
		rvt_pr_err(rdi, "DMA MR not null!\n");

	vfree(rdi->lkey_table.table);
}