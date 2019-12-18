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
struct mxic_spi {int /*<<< orphan*/  send_dly_clk; int /*<<< orphan*/  send_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxic_spi_clk_disable(struct mxic_spi *mxic)
{
	clk_disable_unprepare(mxic->send_clk);
	clk_disable_unprepare(mxic->send_dly_clk);
}