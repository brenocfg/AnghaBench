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
struct fimc_dev {scalar_t__ regs; } ;
struct fimc_addr {int /*<<< orphan*/  cr; int /*<<< orphan*/  cb; int /*<<< orphan*/  y; } ;

/* Variables and functions */
 int FIMC_MAX_OUT_BUFS ; 
 scalar_t__ FIMC_REG_CIOCBSA (int) ; 
 scalar_t__ FIMC_REG_CIOCRSA (int) ; 
 scalar_t__ FIMC_REG_CIOYSA (int) ; 
 int /*<<< orphan*/  dbg (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void fimc_hw_set_output_addr(struct fimc_dev *dev,
			     struct fimc_addr *paddr, int index)
{
	int i = (index == -1) ? 0 : index;
	do {
		writel(paddr->y, dev->regs + FIMC_REG_CIOYSA(i));
		writel(paddr->cb, dev->regs + FIMC_REG_CIOCBSA(i));
		writel(paddr->cr, dev->regs + FIMC_REG_CIOCRSA(i));
		dbg("dst_buf[%d]: 0x%X, cb: 0x%X, cr: 0x%X",
		    i, paddr->y, paddr->cb, paddr->cr);
	} while (index == -1 && ++i < FIMC_MAX_OUT_BUFS);
}