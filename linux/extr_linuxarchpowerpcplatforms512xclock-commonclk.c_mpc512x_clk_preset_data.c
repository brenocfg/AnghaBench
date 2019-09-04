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

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clks ; 

__attribute__((used)) static void mpc512x_clk_preset_data(void)
{
	size_t i;

	for (i = 0; i < ARRAY_SIZE(clks); i++)
		clks[i] = ERR_PTR(-ENODEV);
}