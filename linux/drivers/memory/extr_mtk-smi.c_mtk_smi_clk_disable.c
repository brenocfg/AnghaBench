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
struct mtk_smi {int /*<<< orphan*/  clk_apb; int /*<<< orphan*/  clk_smi; int /*<<< orphan*/  clk_gals0; int /*<<< orphan*/  clk_gals1; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_smi_clk_disable(const struct mtk_smi *smi)
{
	clk_disable_unprepare(smi->clk_gals1);
	clk_disable_unprepare(smi->clk_gals0);
	clk_disable_unprepare(smi->clk_smi);
	clk_disable_unprepare(smi->clk_apb);
}