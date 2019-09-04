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
struct mmp_clk_reset_cell {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void mmp_clk_reset_register(struct device_node *np,
			struct mmp_clk_reset_cell *cells, int nr_resets)
{
}