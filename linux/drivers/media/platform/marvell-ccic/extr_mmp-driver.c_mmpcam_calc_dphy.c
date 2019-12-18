#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mmp_camera_platform_data {int dphy3_algo; int* dphy; int lane_clk; } ;
struct mmp_camera {int /*<<< orphan*/  mipi_clk; TYPE_1__* pdev; } ;
struct mcam_camera {int dummy; } ;
struct device {struct mmp_camera_platform_data* platform_data; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
#define  DPHY3_ALGO_PXA2128 129 
#define  DPHY3_ALGO_PXA910 128 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 struct mmp_camera* mcam_to_cam (struct mcam_camera*) ; 

__attribute__((used)) static void mmpcam_calc_dphy(struct mcam_camera *mcam)
{
	struct mmp_camera *cam = mcam_to_cam(mcam);
	struct mmp_camera_platform_data *pdata = cam->pdev->dev.platform_data;
	struct device *dev = &cam->pdev->dev;
	unsigned long tx_clk_esc;

	/*
	 * If CSI2_DPHY3 is calculated dynamically,
	 * pdata->lane_clk should be already set
	 * either in the board driver statically
	 * or in the sensor driver dynamically.
	 */
	/*
	 * dphy[0] - CSI2_DPHY3:
	 *  bit 0 ~ bit 7: HS Term Enable.
	 *   defines the time that the DPHY
	 *   wait before enabling the data
	 *   lane termination after detecting
	 *   that the sensor has driven the data
	 *   lanes to the LP00 bridge state.
	 *   The value is calculated by:
	 *   (Max T(D_TERM_EN)/Period(DDR)) - 1
	 *  bit 8 ~ bit 15: HS_SETTLE
	 *   Time interval during which the HS
	 *   receiver shall ignore any Data Lane
	 *   HS transitions.
	 *   The value has been calibrated on
	 *   different boards. It seems to work well.
	 *
	 *  More detail please refer
	 *  MIPI Alliance Spectification for D-PHY
	 *  document for explanation of HS-SETTLE
	 *  and D-TERM-EN.
	 */
	switch (pdata->dphy3_algo) {
	case DPHY3_ALGO_PXA910:
		/*
		 * Calculate CSI2_DPHY3 algo for PXA910
		 */
		pdata->dphy[0] =
			(((1 + (pdata->lane_clk * 80) / 1000) & 0xff) << 8)
			| (1 + pdata->lane_clk * 35 / 1000);
		break;
	case DPHY3_ALGO_PXA2128:
		/*
		 * Calculate CSI2_DPHY3 algo for PXA2128
		 */
		pdata->dphy[0] =
			(((2 + (pdata->lane_clk * 110) / 1000) & 0xff) << 8)
			| (1 + pdata->lane_clk * 35 / 1000);
		break;
	default:
		/*
		 * Use default CSI2_DPHY3 value for PXA688/PXA988
		 */
		dev_dbg(dev, "camera: use the default CSI2_DPHY3 value\n");
	}

	/*
	 * mipi_clk will never be changed, it is a fixed value on MMP
	 */
	if (IS_ERR(cam->mipi_clk))
		return;

	/* get the escape clk, this is hard coded */
	clk_prepare_enable(cam->mipi_clk);
	tx_clk_esc = (clk_get_rate(cam->mipi_clk) / 1000000) / 12;
	clk_disable_unprepare(cam->mipi_clk);
	/*
	 * dphy[2] - CSI2_DPHY6:
	 * bit 0 ~ bit 7: CK Term Enable
	 *  Time for the Clock Lane receiver to enable the HS line
	 *  termination. The value is calculated similarly with
	 *  HS Term Enable
	 * bit 8 ~ bit 15: CK Settle
	 *  Time interval during which the HS receiver shall ignore
	 *  any Clock Lane HS transitions.
	 *  The value is calibrated on the boards.
	 */
	pdata->dphy[2] =
		((((534 * tx_clk_esc) / 2000 - 1) & 0xff) << 8)
		| (((38 * tx_clk_esc) / 1000 - 1) & 0xff);

	dev_dbg(dev, "camera: DPHY sets: dphy3=0x%x, dphy5=0x%x, dphy6=0x%x\n",
		pdata->dphy[0], pdata->dphy[1], pdata->dphy[2]);
}