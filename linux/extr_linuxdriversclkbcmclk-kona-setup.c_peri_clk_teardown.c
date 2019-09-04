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
struct peri_clk_data {int /*<<< orphan*/  sel; } ;
struct clk_init_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_sel_teardown (int /*<<< orphan*/ *,struct clk_init_data*) ; 

__attribute__((used)) static void peri_clk_teardown(struct peri_clk_data *data,
				struct clk_init_data *init_data)
{
	clk_sel_teardown(&data->sel, init_data);
}