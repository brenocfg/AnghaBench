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
struct mcam_camera {int* dphy; int mipi_enabled; int lane; int mclk_src; int mclk_div; } ;

/* Variables and functions */
 int CSI2_C0_ACT_LANE (int) ; 
 int CSI2_C0_MIPI_EN ; 
 int /*<<< orphan*/  REG_CLKCTRL ; 
 int /*<<< orphan*/  REG_CSI2_CTRL0 ; 
 int /*<<< orphan*/  REG_CSI2_DPHY3 ; 
 int /*<<< orphan*/  REG_CSI2_DPHY5 ; 
 int /*<<< orphan*/  REG_CSI2_DPHY6 ; 
 int /*<<< orphan*/  cam_dbg (struct mcam_camera*,char*,int,int,int) ; 
 int /*<<< orphan*/  cam_warn (struct mcam_camera*,char*) ; 
 int /*<<< orphan*/  mcam_reg_write (struct mcam_camera*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mcam_enable_mipi(struct mcam_camera *mcam)
{
	/* Using MIPI mode and enable MIPI */
	cam_dbg(mcam, "camera: DPHY3=0x%x, DPHY5=0x%x, DPHY6=0x%x\n",
			mcam->dphy[0], mcam->dphy[1], mcam->dphy[2]);
	mcam_reg_write(mcam, REG_CSI2_DPHY3, mcam->dphy[0]);
	mcam_reg_write(mcam, REG_CSI2_DPHY5, mcam->dphy[1]);
	mcam_reg_write(mcam, REG_CSI2_DPHY6, mcam->dphy[2]);

	if (!mcam->mipi_enabled) {
		if (mcam->lane > 4 || mcam->lane <= 0) {
			cam_warn(mcam, "lane number error\n");
			mcam->lane = 1;	/* set the default value */
		}
		/*
		 * 0x41 actives 1 lane
		 * 0x43 actives 2 lanes
		 * 0x45 actives 3 lanes (never happen)
		 * 0x47 actives 4 lanes
		 */
		mcam_reg_write(mcam, REG_CSI2_CTRL0,
			CSI2_C0_MIPI_EN | CSI2_C0_ACT_LANE(mcam->lane));
		mcam_reg_write(mcam, REG_CLKCTRL,
			(mcam->mclk_src << 29) | mcam->mclk_div);

		mcam->mipi_enabled = true;
	}
}