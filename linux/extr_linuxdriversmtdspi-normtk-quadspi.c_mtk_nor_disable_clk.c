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
struct mtk_nor {int /*<<< orphan*/  nor_clk; int /*<<< orphan*/  spi_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_nor_disable_clk(struct mtk_nor *mtk_nor)
{
	clk_disable_unprepare(mtk_nor->spi_clk);
	clk_disable_unprepare(mtk_nor->nor_clk);
}