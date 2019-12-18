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
struct sunxi_ir {int /*<<< orphan*/  rc; int /*<<< orphan*/  ir_lock; scalar_t__ base; int /*<<< orphan*/  rst; int /*<<< orphan*/  apb_clk; int /*<<< orphan*/  clk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_RXSTA_CLEARALL ; 
 scalar_t__ SUNXI_IR_CTL_REG ; 
 scalar_t__ SUNXI_IR_RXINT_REG ; 
 scalar_t__ SUNXI_IR_RXSTA_REG ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sunxi_ir* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sunxi_ir_remove(struct platform_device *pdev)
{
	unsigned long flags;
	struct sunxi_ir *ir = platform_get_drvdata(pdev);

	clk_disable_unprepare(ir->clk);
	clk_disable_unprepare(ir->apb_clk);
	reset_control_assert(ir->rst);

	spin_lock_irqsave(&ir->ir_lock, flags);
	/* disable IR IRQ */
	writel(0, ir->base + SUNXI_IR_RXINT_REG);
	/* clear All Rx Interrupt Status */
	writel(REG_RXSTA_CLEARALL, ir->base + SUNXI_IR_RXSTA_REG);
	/* disable IR */
	writel(0, ir->base + SUNXI_IR_CTL_REG);
	spin_unlock_irqrestore(&ir->ir_lock, flags);

	rc_unregister_device(ir->rc);
	return 0;
}