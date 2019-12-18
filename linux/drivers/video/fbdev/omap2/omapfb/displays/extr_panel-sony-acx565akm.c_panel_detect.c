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
struct panel_drv_data {int* display_id; char* name; int has_bc; int has_cabc; int revision; TYPE_1__* spi; int /*<<< orphan*/  model; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MIPID_CMD_READ_DISP_ID ; 
 int /*<<< orphan*/  MIPID_VER_ACX565AKM ; 
 int /*<<< orphan*/  MIPID_VER_L4F00311 ; 
 int /*<<< orphan*/  MIPID_VER_LPH8923 ; 
 int /*<<< orphan*/  MIPID_VER_LS041Y3 ; 
 int /*<<< orphan*/  acx565akm_read (struct panel_drv_data*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,int) ; 

__attribute__((used)) static int panel_detect(struct panel_drv_data *ddata)
{
	acx565akm_read(ddata, MIPID_CMD_READ_DISP_ID, ddata->display_id, 3);
	dev_dbg(&ddata->spi->dev, "MIPI display ID: %02x%02x%02x\n",
		ddata->display_id[0],
		ddata->display_id[1],
		ddata->display_id[2]);

	switch (ddata->display_id[0]) {
	case 0x10:
		ddata->model = MIPID_VER_ACX565AKM;
		ddata->name = "acx565akm";
		ddata->has_bc = 1;
		ddata->has_cabc = 1;
		break;
	case 0x29:
		ddata->model = MIPID_VER_L4F00311;
		ddata->name = "l4f00311";
		break;
	case 0x45:
		ddata->model = MIPID_VER_LPH8923;
		ddata->name = "lph8923";
		break;
	case 0x83:
		ddata->model = MIPID_VER_LS041Y3;
		ddata->name = "ls041y3";
		break;
	default:
		ddata->name = "unknown";
		dev_err(&ddata->spi->dev, "invalid display ID\n");
		return -ENODEV;
	}

	ddata->revision = ddata->display_id[1];

	dev_info(&ddata->spi->dev, "omapfb: %s rev %02x LCD detected\n",
			ddata->name, ddata->revision);

	return 0;
}