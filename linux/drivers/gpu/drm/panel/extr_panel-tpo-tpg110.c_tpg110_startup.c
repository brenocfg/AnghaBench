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
typedef  int u8 ;
struct tpg110_panel_mode {int magic; } ;
struct tpg110 {int /*<<< orphan*/  dev; struct tpg110_panel_mode const* panel_mode; int /*<<< orphan*/  grestb; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct tpg110_panel_mode*) ; 
 int /*<<< orphan*/  DRM_DEV_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DRM_DEV_INFO (int /*<<< orphan*/ ,char*,...) ; 
 int ENODEV ; 
 int /*<<< orphan*/  TPG110_CHIPID ; 
 int /*<<< orphan*/  TPG110_CTRL1 ; 
 int /*<<< orphan*/  TPG110_CTRL2 ; 
 int TPG110_CTRL2_RES_PM_CTRL ; 
#define  TPG110_RES_400X240_D 133 
#define  TPG110_RES_480X272 132 
#define  TPG110_RES_480X272_D 131 
#define  TPG110_RES_480X640 130 
#define  TPG110_RES_640X480 129 
#define  TPG110_RES_800X480 128 
 int TPG110_RES_MASK ; 
 int /*<<< orphan*/  TPG110_TEST ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tpg110_panel_mode* tpg110_modes ; 
 int tpg110_read_reg (struct tpg110*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpg110_write_reg (struct tpg110*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tpg110_startup(struct tpg110 *tpg)
{
	u8 val;
	int i;

	/* De-assert the reset signal */
	gpiod_set_value_cansleep(tpg->grestb, 0);
	usleep_range(1000, 2000);
	DRM_DEV_DEBUG(tpg->dev, "de-asserted GRESTB\n");

	/* Test display communication */
	tpg110_write_reg(tpg, TPG110_TEST, 0x55);
	val = tpg110_read_reg(tpg, TPG110_TEST);
	if (val != 0x55) {
		DRM_DEV_ERROR(tpg->dev, "failed communication test\n");
		return -ENODEV;
	}

	val = tpg110_read_reg(tpg, TPG110_CHIPID);
	DRM_DEV_INFO(tpg->dev, "TPG110 chip ID: %d version: %d\n",
		 val >> 4, val & 0x0f);

	/* Show display resolution */
	val = tpg110_read_reg(tpg, TPG110_CTRL1);
	val &= TPG110_RES_MASK;
	switch (val) {
	case TPG110_RES_400X240_D:
		DRM_DEV_INFO(tpg->dev,
			 "IN 400x240 RGB -> OUT 800x480 RGB (dual scan)\n");
		break;
	case TPG110_RES_480X272_D:
		DRM_DEV_INFO(tpg->dev,
			 "IN 480x272 RGB -> OUT 800x480 RGB (dual scan)\n");
		break;
	case TPG110_RES_480X640:
		DRM_DEV_INFO(tpg->dev, "480x640 RGB\n");
		break;
	case TPG110_RES_480X272:
		DRM_DEV_INFO(tpg->dev, "480x272 RGB\n");
		break;
	case TPG110_RES_640X480:
		DRM_DEV_INFO(tpg->dev, "640x480 RGB\n");
		break;
	case TPG110_RES_800X480:
		DRM_DEV_INFO(tpg->dev, "800x480 RGB\n");
		break;
	default:
		DRM_DEV_ERROR(tpg->dev, "ILLEGAL RESOLUTION 0x%02x\n", val);
		break;
	}

	/* From the producer side, this is the same resolution */
	if (val == TPG110_RES_480X272_D)
		val = TPG110_RES_480X272;

	for (i = 0; i < ARRAY_SIZE(tpg110_modes); i++) {
		const struct tpg110_panel_mode *pm;

		pm = &tpg110_modes[i];
		if (pm->magic == val) {
			tpg->panel_mode = pm;
			break;
		}
	}
	if (i == ARRAY_SIZE(tpg110_modes)) {
		DRM_DEV_ERROR(tpg->dev, "unsupported mode (%02x) detected\n",
			val);
		return -ENODEV;
	}

	val = tpg110_read_reg(tpg, TPG110_CTRL2);
	DRM_DEV_INFO(tpg->dev, "resolution and standby is controlled by %s\n",
		 (val & TPG110_CTRL2_RES_PM_CTRL) ? "software" : "hardware");
	/* Take control over resolution and standby */
	val |= TPG110_CTRL2_RES_PM_CTRL;
	tpg110_write_reg(tpg, TPG110_CTRL2, val);

	return 0;
}