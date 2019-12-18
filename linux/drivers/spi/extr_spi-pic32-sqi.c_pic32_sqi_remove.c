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
struct pic32_sqi {int /*<<< orphan*/  sys_clk; int /*<<< orphan*/  base_clk; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pic32_sqi*) ; 
 struct pic32_sqi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  ring_desc_ring_free (struct pic32_sqi*) ; 

__attribute__((used)) static int pic32_sqi_remove(struct platform_device *pdev)
{
	struct pic32_sqi *sqi = platform_get_drvdata(pdev);

	/* release resources */
	free_irq(sqi->irq, sqi);
	ring_desc_ring_free(sqi);

	/* disable clk */
	clk_disable_unprepare(sqi->base_clk);
	clk_disable_unprepare(sqi->sys_clk);

	return 0;
}