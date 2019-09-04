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
struct mtk_hsdma_device {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_HSDMA_GLO ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsdma2dev (struct mtk_hsdma_device*) ; 
 int /*<<< orphan*/  mtk_dma_write (struct mtk_hsdma_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_hsdma_hw_deinit(struct mtk_hsdma_device *hsdma)
{
	mtk_dma_write(hsdma, MTK_HSDMA_GLO, 0);

	clk_disable_unprepare(hsdma->clk);

	pm_runtime_put_sync(hsdma2dev(hsdma));
	pm_runtime_disable(hsdma2dev(hsdma));

	return 0;
}