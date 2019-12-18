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
struct lpuart_port {int /*<<< orphan*/  ipg_clk; int /*<<< orphan*/  baud_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __lpuart_enable_clks(struct lpuart_port *sport, bool is_en)
{
	int ret = 0;

	if (is_en) {
		ret = clk_prepare_enable(sport->ipg_clk);
		if (ret)
			return ret;

		ret = clk_prepare_enable(sport->baud_clk);
		if (ret) {
			clk_disable_unprepare(sport->ipg_clk);
			return ret;
		}
	} else {
		clk_disable_unprepare(sport->baud_clk);
		clk_disable_unprepare(sport->ipg_clk);
	}

	return 0;
}