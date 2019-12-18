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
typedef  int u32 ;
struct goldfish_fb {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; int /*<<< orphan*/  base_update_count; scalar_t__ reg_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int FB_INT_BASE_UPDATE_DONE ; 
 scalar_t__ FB_INT_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t goldfish_fb_interrupt(int irq, void *dev_id)
{
	unsigned long irq_flags;
	struct goldfish_fb *fb = dev_id;
	u32 status;

	spin_lock_irqsave(&fb->lock, irq_flags);
	status = readl(fb->reg_base + FB_INT_STATUS);
	if (status & FB_INT_BASE_UPDATE_DONE) {
		fb->base_update_count++;
		wake_up(&fb->wait);
	}
	spin_unlock_irqrestore(&fb->lock, irq_flags);
	return status ? IRQ_HANDLED : IRQ_NONE;
}