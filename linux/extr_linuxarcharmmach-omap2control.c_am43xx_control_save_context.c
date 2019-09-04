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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * am33xx_control_vals ; 
 int /*<<< orphan*/ * am43xx_control_reg_offsets ; 
 int /*<<< orphan*/  omap_ctrl_readl (int /*<<< orphan*/ ) ; 

void am43xx_control_save_context(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(am43xx_control_reg_offsets); i++)
		am33xx_control_vals[i] =
				omap_ctrl_readl(am43xx_control_reg_offsets[i]);
}