#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;
struct img_i2c {int int_enable; int /*<<< orphan*/  lock; TYPE_2__ adap; } ;

/* Variables and functions */
 int INT_SLAVE_EVENT ; 
 unsigned int LINESTAT_ABORT_DET ; 
 int /*<<< orphan*/  SCB_INT_MASK_REG ; 
 int /*<<< orphan*/  SCB_STATUS_REG ; 
 int /*<<< orphan*/  check_timer ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct img_i2c* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct img_i2c* i2c ; 
 unsigned int img_i2c_readl (struct img_i2c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2c_writel (struct img_i2c*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void img_i2c_check_timer(struct timer_list *t)
{
	struct img_i2c *i2c = from_timer(i2c, t, check_timer);
	unsigned long flags;
	unsigned int line_status;

	spin_lock_irqsave(&i2c->lock, flags);
	line_status = img_i2c_readl(i2c, SCB_STATUS_REG);

	/* check for an abort condition */
	if (line_status & LINESTAT_ABORT_DET) {
		dev_dbg(i2c->adap.dev.parent,
			"abort condition detected by check timer\n");
		/* enable slave event interrupt mask to trigger irq */
		img_i2c_writel(i2c, SCB_INT_MASK_REG,
			       i2c->int_enable | INT_SLAVE_EVENT);
	}

	spin_unlock_irqrestore(&i2c->lock, flags);
}