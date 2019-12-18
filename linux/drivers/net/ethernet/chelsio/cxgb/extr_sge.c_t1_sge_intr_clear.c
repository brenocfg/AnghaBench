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
struct sge {TYPE_1__* adapter; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ A_PL_CAUSE ; 
 scalar_t__ A_SG_INT_CAUSE ; 
 int SGE_PL_INTR_MASK ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void t1_sge_intr_clear(struct sge *sge)
{
	writel(SGE_PL_INTR_MASK, sge->adapter->regs + A_PL_CAUSE);
	writel(0xffffffff, sge->adapter->regs + A_SG_INT_CAUSE);
}