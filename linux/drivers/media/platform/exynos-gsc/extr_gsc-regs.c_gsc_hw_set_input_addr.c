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
struct gsc_dev {scalar_t__ regs; } ;
struct gsc_addr {int /*<<< orphan*/  cr; int /*<<< orphan*/  cb; int /*<<< orphan*/  y; } ;

/* Variables and functions */
 scalar_t__ GSC_IN_BASE_ADDR_CB (int) ; 
 scalar_t__ GSC_IN_BASE_ADDR_CR (int) ; 
 scalar_t__ GSC_IN_BASE_ADDR_Y (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void gsc_hw_set_input_addr(struct gsc_dev *dev, struct gsc_addr *addr,
				int index)
{
	pr_debug("src_buf[%d]: %pad, cb: %pad, cr: %pad", index,
			&addr->y, &addr->cb, &addr->cr);
	writel(addr->y, dev->regs + GSC_IN_BASE_ADDR_Y(index));
	writel(addr->cb, dev->regs + GSC_IN_BASE_ADDR_CB(index));
	writel(addr->cr, dev->regs + GSC_IN_BASE_ADDR_CR(index));

}