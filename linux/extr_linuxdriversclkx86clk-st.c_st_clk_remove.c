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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ST_MAX_CLKS ; 
 int /*<<< orphan*/  clk_hw_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hws ; 

__attribute__((used)) static int st_clk_remove(struct platform_device *pdev)
{
	int i;

	for (i = 0; i < ST_MAX_CLKS; i++)
		clk_hw_unregister(hws[i]);
	return 0;
}