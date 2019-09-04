#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct pmac_i2c_host_kw {scalar_t__ state; int /*<<< orphan*/  lock; TYPE_1__ timeout_timer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ KW_POLL_TIMEOUT ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kw_i2c_handle_interrupt (struct pmac_i2c_host_kw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kw_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_isr ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ state_idle ; 

__attribute__((used)) static irqreturn_t kw_i2c_irq(int irq, void *dev_id)
{
	struct pmac_i2c_host_kw *host = dev_id;
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);
	del_timer(&host->timeout_timer);
	kw_i2c_handle_interrupt(host, kw_read_reg(reg_isr));
	if (host->state != state_idle) {
		host->timeout_timer.expires = jiffies + KW_POLL_TIMEOUT;
		add_timer(&host->timeout_timer);
	}
	spin_unlock_irqrestore(&host->lock, flags);
	return IRQ_HANDLED;
}