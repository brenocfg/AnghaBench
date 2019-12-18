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
struct mtk_cec {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_cec_htplg_irq_disable (struct mtk_cec*) ; 
 struct mtk_cec* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mtk_cec_remove(struct platform_device *pdev)
{
	struct mtk_cec *cec = platform_get_drvdata(pdev);

	mtk_cec_htplg_irq_disable(cec);
	clk_disable_unprepare(cec->clk);
	return 0;
}