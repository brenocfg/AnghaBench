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
struct clk_plt_data {int /*<<< orphan*/  nparents; } ;

/* Variables and functions */
 int /*<<< orphan*/  plt_clk_unregister_fixed_rate_loop (struct clk_plt_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void plt_clk_unregister_parents(struct clk_plt_data *data)
{
	plt_clk_unregister_fixed_rate_loop(data, data->nparents);
}