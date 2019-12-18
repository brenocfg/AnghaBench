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
struct platform_device {int dummy; } ;
struct mtk_ir {int /*<<< orphan*/  clk; int /*<<< orphan*/  bus; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_IRINT_EN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_irq_disable (struct mtk_ir*,int /*<<< orphan*/ ) ; 
 struct mtk_ir* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_ir_remove(struct platform_device *pdev)
{
	struct mtk_ir *ir = platform_get_drvdata(pdev);

	/*
	 * Avoid contention between remove handler and
	 * IRQ handler so that disabling IR interrupt and
	 * waiting for pending IRQ handler to complete
	 */
	mtk_irq_disable(ir, MTK_IRINT_EN);
	synchronize_irq(ir->irq);

	clk_disable_unprepare(ir->bus);
	clk_disable_unprepare(ir->clk);

	return 0;
}