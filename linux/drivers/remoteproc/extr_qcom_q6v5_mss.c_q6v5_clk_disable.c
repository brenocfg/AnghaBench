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
struct device {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 

__attribute__((used)) static void q6v5_clk_disable(struct device *dev,
			     struct clk **clks, int count)
{
	int i;

	for (i = 0; i < count; i++)
		clk_disable_unprepare(clks[i]);
}