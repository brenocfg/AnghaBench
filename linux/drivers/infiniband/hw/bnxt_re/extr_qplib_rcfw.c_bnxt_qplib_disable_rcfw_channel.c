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
struct bnxt_qplib_rcfw {unsigned long bmap_size; scalar_t__ vector; int /*<<< orphan*/ * aeq_handler; int /*<<< orphan*/ * creq_bar_reg_iomem; int /*<<< orphan*/ * cmdq_bar_reg_iomem; int /*<<< orphan*/  cmdq_bitmap; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_qplib_rcfw_stop_irq (struct bnxt_qplib_rcfw*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned long) ; 
 unsigned long find_first_bit (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void bnxt_qplib_disable_rcfw_channel(struct bnxt_qplib_rcfw *rcfw)
{
	unsigned long indx;

	bnxt_qplib_rcfw_stop_irq(rcfw, true);

	iounmap(rcfw->cmdq_bar_reg_iomem);
	iounmap(rcfw->creq_bar_reg_iomem);

	indx = find_first_bit(rcfw->cmdq_bitmap, rcfw->bmap_size);
	if (indx != rcfw->bmap_size)
		dev_err(&rcfw->pdev->dev,
			"disabling RCFW with pending cmd-bit %lx\n", indx);
	kfree(rcfw->cmdq_bitmap);
	rcfw->bmap_size = 0;

	rcfw->cmdq_bar_reg_iomem = NULL;
	rcfw->creq_bar_reg_iomem = NULL;
	rcfw->aeq_handler = NULL;
	rcfw->vector = 0;
}