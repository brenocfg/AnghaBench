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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB0H_READ_WAKEUP_ACK ; 
 int MBOX_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRCM_MBOX_CPU_SET ; 
 int /*<<< orphan*/  PRCM_MBOX_CPU_VAL ; 
 scalar_t__ PRCM_MBOX_HEADER_REQ_MB0 ; 
 int /*<<< orphan*/  cpu_relax () ; 
 TYPE_1__ mb0_transfer ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ tcdm_base ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ack_dbb_wakeup(void)
{
	unsigned long flags;

	spin_lock_irqsave(&mb0_transfer.lock, flags);

	while (readl(PRCM_MBOX_CPU_VAL) & MBOX_BIT(0))
		cpu_relax();

	writeb(MB0H_READ_WAKEUP_ACK, (tcdm_base + PRCM_MBOX_HEADER_REQ_MB0));
	writel(MBOX_BIT(0), PRCM_MBOX_CPU_SET);

	spin_unlock_irqrestore(&mb0_transfer.lock, flags);
}