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
struct st_rc_device {scalar_t__ rx_base; } ;
struct rc_dev {struct st_rc_device* priv; } ;

/* Variables and functions */
 scalar_t__ IRB_RX_EN ; 
 int IRB_RX_INTS ; 
 scalar_t__ IRB_RX_INT_EN ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int st_rc_open(struct rc_dev *rdev)
{
	struct st_rc_device *dev = rdev->priv;
	unsigned long flags;
	local_irq_save(flags);
	/* enable interrupts and receiver */
	writel(IRB_RX_INTS, dev->rx_base + IRB_RX_INT_EN);
	writel(0x01, dev->rx_base + IRB_RX_EN);
	local_irq_restore(flags);

	return 0;
}