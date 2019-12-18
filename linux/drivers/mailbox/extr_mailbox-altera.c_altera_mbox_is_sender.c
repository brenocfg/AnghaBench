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
typedef  scalar_t__ u32 ;
struct altera_mbox {scalar_t__ mbox_base; } ;

/* Variables and functions */
 scalar_t__ MAILBOX_PTR_REG ; 
 scalar_t__ MBOX_MAGIC ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static bool altera_mbox_is_sender(struct altera_mbox *mbox)
{
	u32 reg;
	/* Write a magic number to PTR register and read back this register.
	 * This register is read-write if it is a sender.
	 */
	#define MBOX_MAGIC	0xA5A5AA55
	writel_relaxed(MBOX_MAGIC, mbox->mbox_base + MAILBOX_PTR_REG);
	reg = readl_relaxed(mbox->mbox_base + MAILBOX_PTR_REG);
	if (reg == MBOX_MAGIC) {
		/* Clear to 0 */
		writel_relaxed(0, mbox->mbox_base + MAILBOX_PTR_REG);
		return true;
	}
	return false;
}