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
struct tegra_cec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_CEC_HW_CONTROL ; 
 int /*<<< orphan*/  TEGRA_CEC_INT_STAT ; 
 int cec_read (struct tegra_cec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_write (struct tegra_cec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tegra_cec_error_recovery(struct tegra_cec *cec)
{
	u32 hw_ctrl;

	hw_ctrl = cec_read(cec, TEGRA_CEC_HW_CONTROL);
	cec_write(cec, TEGRA_CEC_HW_CONTROL, 0);
	cec_write(cec, TEGRA_CEC_INT_STAT, 0xffffffff);
	cec_write(cec, TEGRA_CEC_HW_CONTROL, hw_ctrl);
}