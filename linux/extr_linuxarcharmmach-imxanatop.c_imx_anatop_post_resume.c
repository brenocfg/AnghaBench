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
 scalar_t__ IMX_DDR_TYPE_LPDDR2 ; 
 scalar_t__ cpu_is_imx6sl () ; 
 int /*<<< orphan*/  imx_anatop_disconnect_high_snvs (int) ; 
 int /*<<< orphan*/  imx_anatop_enable_2p5_pulldown (int) ; 
 int /*<<< orphan*/  imx_anatop_enable_fet_odrive (int) ; 
 int /*<<< orphan*/  imx_anatop_enable_weak2p5 (int) ; 
 scalar_t__ imx_mmdc_get_ddr_type () ; 

void imx_anatop_post_resume(void)
{
	if (imx_mmdc_get_ddr_type() == IMX_DDR_TYPE_LPDDR2)
		imx_anatop_enable_2p5_pulldown(false);
	else
		imx_anatop_enable_weak2p5(false);

	imx_anatop_enable_fet_odrive(false);

	if (cpu_is_imx6sl())
		imx_anatop_disconnect_high_snvs(false);

}