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
 int /*<<< orphan*/  DM355_VIN_CAM_HD ; 
 int /*<<< orphan*/  DM355_VIN_CAM_VD ; 
 int /*<<< orphan*/  DM355_VIN_CAM_WEN ; 
 int /*<<< orphan*/  DM355_VIN_CINH_EN ; 
 int /*<<< orphan*/  DM355_VIN_CINL_EN ; 
 int /*<<< orphan*/  DM355_VIN_PCLK ; 
 int /*<<< orphan*/  DM355_VIN_YIN_EN ; 
 int /*<<< orphan*/  davinci_cfg_reg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm355_ccdc_setup_pinmux(void)
{
	davinci_cfg_reg(DM355_VIN_PCLK);
	davinci_cfg_reg(DM355_VIN_CAM_WEN);
	davinci_cfg_reg(DM355_VIN_CAM_VD);
	davinci_cfg_reg(DM355_VIN_CAM_HD);
	davinci_cfg_reg(DM355_VIN_YIN_EN);
	davinci_cfg_reg(DM355_VIN_CINL_EN);
	davinci_cfg_reg(DM355_VIN_CINH_EN);
}