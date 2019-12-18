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
struct mxic_spi {int /*<<< orphan*/  send_clk; int /*<<< orphan*/  send_dly_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxic_spi_clk_enable(struct mxic_spi *mxic)
{
	int ret;

	ret = clk_prepare_enable(mxic->send_clk);
	if (ret)
		return ret;

	ret = clk_prepare_enable(mxic->send_dly_clk);
	if (ret)
		goto err_send_dly_clk;

	return ret;

err_send_dly_clk:
	clk_disable_unprepare(mxic->send_clk);

	return ret;
}