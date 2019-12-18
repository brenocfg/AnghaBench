#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct s3c24xx_uart_port {struct s3c24xx_uart_info* info; TYPE_2__ port; TYPE_1__* cfg; } ;
struct s3c24xx_uart_info {unsigned int def_clk_sel; unsigned int num_clks; scalar_t__ has_divslot; } ;
struct clk {int dummy; } ;
struct TYPE_3__ {int clk_sel; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int MAX_CLK_NAME_LENGTH ; 
 struct clk* clk_get (int /*<<< orphan*/ ,char*) ; 
 unsigned long clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static unsigned int s3c24xx_serial_getclk(struct s3c24xx_uart_port *ourport,
			unsigned int req_baud, struct clk **best_clk,
			unsigned int *clk_num)
{
	struct s3c24xx_uart_info *info = ourport->info;
	struct clk *clk;
	unsigned long rate;
	unsigned int cnt, baud, quot, clk_sel, best_quot = 0;
	char clkname[MAX_CLK_NAME_LENGTH];
	int calc_deviation, deviation = (1 << 30) - 1;

	clk_sel = (ourport->cfg->clk_sel) ? ourport->cfg->clk_sel :
			ourport->info->def_clk_sel;
	for (cnt = 0; cnt < info->num_clks; cnt++) {
		if (!(clk_sel & (1 << cnt)))
			continue;

		sprintf(clkname, "clk_uart_baud%d", cnt);
		clk = clk_get(ourport->port.dev, clkname);
		if (IS_ERR(clk))
			continue;

		rate = clk_get_rate(clk);
		if (!rate)
			continue;

		if (ourport->info->has_divslot) {
			unsigned long div = rate / req_baud;

			/* The UDIVSLOT register on the newer UARTs allows us to
			 * get a divisor adjustment of 1/16th on the baud clock.
			 *
			 * We don't keep the UDIVSLOT value (the 16ths we
			 * calculated by not multiplying the baud by 16) as it
			 * is easy enough to recalculate.
			 */

			quot = div / 16;
			baud = rate / div;
		} else {
			quot = (rate + (8 * req_baud)) / (16 * req_baud);
			baud = rate / (quot * 16);
		}
		quot--;

		calc_deviation = req_baud - baud;
		if (calc_deviation < 0)
			calc_deviation = -calc_deviation;

		if (calc_deviation < deviation) {
			*best_clk = clk;
			best_quot = quot;
			*clk_num = cnt;
			deviation = calc_deviation;
		}
	}

	return best_quot;
}