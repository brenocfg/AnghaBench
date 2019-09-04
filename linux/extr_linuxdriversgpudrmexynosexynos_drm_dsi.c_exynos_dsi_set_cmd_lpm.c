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
typedef  int /*<<< orphan*/  u32 ;
struct exynos_dsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSIM_CMD_LPDT_LP ; 
 int /*<<< orphan*/  DSIM_ESCMODE_REG ; 
 int /*<<< orphan*/  exynos_dsi_read (struct exynos_dsi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_dsi_write (struct exynos_dsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_dsi_set_cmd_lpm(struct exynos_dsi *dsi, bool lpm)
{
	u32 v = exynos_dsi_read(dsi, DSIM_ESCMODE_REG);

	if (lpm)
		v |= DSIM_CMD_LPDT_LP;
	else
		v &= ~DSIM_CMD_LPDT_LP;

	exynos_dsi_write(dsi, DSIM_ESCMODE_REG, v);
}