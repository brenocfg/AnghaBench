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
struct peri_clk_data {int /*<<< orphan*/  sel; int /*<<< orphan*/  clocks; } ;
struct clk_init_data {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_IGNORE_UNUSED ; 
 int clk_sel_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct clk_init_data*) ; 

__attribute__((used)) static int
peri_clk_setup(struct peri_clk_data *data, struct clk_init_data *init_data)
{
	init_data->flags = CLK_IGNORE_UNUSED;

	return clk_sel_setup(data->clocks, &data->sel, init_data);
}