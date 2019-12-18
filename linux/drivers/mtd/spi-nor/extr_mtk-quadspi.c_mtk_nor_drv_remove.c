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
struct mtk_nor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtk_nor_disable_clk (struct mtk_nor*) ; 
 struct mtk_nor* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mtk_nor_drv_remove(struct platform_device *pdev)
{
	struct mtk_nor *mtk_nor = platform_get_drvdata(pdev);

	mtk_nor_disable_clk(mtk_nor);

	return 0;
}