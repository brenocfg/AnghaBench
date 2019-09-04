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
struct meson_clk_mpll_data {int dummy; } ;
struct clk_regmap {scalar_t__ data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct meson_clk_mpll_data *
meson_clk_mpll_data(struct clk_regmap *clk)
{
	return (struct meson_clk_mpll_data *)clk->data;
}