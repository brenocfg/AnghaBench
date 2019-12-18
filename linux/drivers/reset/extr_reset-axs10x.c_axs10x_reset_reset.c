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
struct reset_controller_dev {int dummy; } ;
struct axs10x_rst {int /*<<< orphan*/  lock; int /*<<< orphan*/  regs_rst; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct axs10x_rst* to_axs10x_rst (struct reset_controller_dev*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axs10x_reset_reset(struct reset_controller_dev *rcdev,
			      unsigned long id)
{
	struct axs10x_rst *rst = to_axs10x_rst(rcdev);
	unsigned long flags;

	spin_lock_irqsave(&rst->lock, flags);
	writel(BIT(id), rst->regs_rst);
	spin_unlock_irqrestore(&rst->lock, flags);

	return 0;
}