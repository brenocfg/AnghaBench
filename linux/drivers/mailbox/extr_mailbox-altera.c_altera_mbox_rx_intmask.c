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
typedef  int /*<<< orphan*/  u32 ;
struct altera_mbox {scalar_t__ mbox_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_PENDING_MSK ; 
 scalar_t__ MAILBOX_INTMASK_REG ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void altera_mbox_rx_intmask(struct altera_mbox *mbox, bool enable)
{
	u32 mask;

	mask = readl_relaxed(mbox->mbox_base + MAILBOX_INTMASK_REG);
	if (enable)
		mask |= INT_PENDING_MSK;
	else
		mask &= ~INT_PENDING_MSK;
	writel_relaxed(mask, mbox->mbox_base + MAILBOX_INTMASK_REG);
}