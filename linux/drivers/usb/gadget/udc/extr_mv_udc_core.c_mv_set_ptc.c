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
typedef  int u32 ;
struct mv_udc {TYPE_1__* op_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/ * portsc; } ;

/* Variables and functions */
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mv_set_ptc(struct mv_udc *udc, u32 mode)
{
	u32 portsc;

	portsc = readl(&udc->op_regs->portsc[0]);
	portsc |= mode << 16;
	writel(portsc, &udc->op_regs->portsc[0]);
}