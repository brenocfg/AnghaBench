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
typedef  int u32 ;
struct tegra_dfll {int lut_min; int lut_max; int i2c_lut_size; int lut_safe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFLL_INTR_EN ; 
 int DFLL_INTR_MAX_MASK ; 
 int DFLL_INTR_MIN_MASK ; 
 int /*<<< orphan*/  DFLL_INTR_STS ; 
 int /*<<< orphan*/  DFLL_OUTPUT_CFG ; 
 int DFLL_OUTPUT_CFG_MAX_SHIFT ; 
 int DFLL_OUTPUT_CFG_MIN_SHIFT ; 
 int DFLL_OUTPUT_CFG_SAFE_SHIFT ; 
 int /*<<< orphan*/  DFLL_OUTPUT_FORCE ; 
 int /*<<< orphan*/  dfll_i2c_wmb (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_i2c_writel (struct tegra_dfll*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dfll_init_i2c_if (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_load_i2c_lut (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_writel (struct tegra_dfll*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dfll_init_out_if(struct tegra_dfll *td)
{
	u32 val;

	td->lut_min = 0;
	td->lut_max = td->i2c_lut_size - 1;
	td->lut_safe = td->lut_min + 1;

	dfll_i2c_writel(td, 0, DFLL_OUTPUT_CFG);
	val = (td->lut_safe << DFLL_OUTPUT_CFG_SAFE_SHIFT) |
		(td->lut_max << DFLL_OUTPUT_CFG_MAX_SHIFT) |
		(td->lut_min << DFLL_OUTPUT_CFG_MIN_SHIFT);
	dfll_i2c_writel(td, val, DFLL_OUTPUT_CFG);
	dfll_i2c_wmb(td);

	dfll_writel(td, 0, DFLL_OUTPUT_FORCE);
	dfll_i2c_writel(td, 0, DFLL_INTR_EN);
	dfll_i2c_writel(td, DFLL_INTR_MAX_MASK | DFLL_INTR_MIN_MASK,
			DFLL_INTR_STS);

	dfll_load_i2c_lut(td);
	dfll_init_i2c_if(td);
}