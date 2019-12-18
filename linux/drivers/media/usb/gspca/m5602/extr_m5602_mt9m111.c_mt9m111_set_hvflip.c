#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sd {TYPE_2__* vflip; TYPE_1__* hflip; } ;
struct TYPE_6__ {int width; } ;
struct gspca_dev {TYPE_3__ pixfmt; } ;
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
struct TYPE_4__ {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  MT9M111_PAGE_MAP ; 
 int MT9M111_RMB_COLUMN_SKIP_2X ; 
 int MT9M111_RMB_COLUMN_SKIP_4X ; 
 int MT9M111_RMB_OVER_SIZED ; 
 int MT9M111_RMB_ROW_SKIP_2X ; 
 int MT9M111_RMB_ROW_SKIP_4X ; 
 int /*<<< orphan*/  MT9M111_SC_R_MODE_CONTEXT_B ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int mt9m111_set_hvflip(struct gspca_dev *gspca_dev)
{
	int err;
	u8 data[2] = {0x00, 0x00};
	struct sd *sd = (struct sd *) gspca_dev;
	int hflip;
	int vflip;

	gspca_dbg(gspca_dev, D_CONF, "Set hvflip to %d %d\n",
		  sd->hflip->val, sd->vflip->val);

	/* The mt9m111 is flipped by default */
	hflip = !sd->hflip->val;
	vflip = !sd->vflip->val;

	/* Set the correct page map */
	err = m5602_write_sensor(sd, MT9M111_PAGE_MAP, data, 2);
	if (err < 0)
		return err;

	data[0] = MT9M111_RMB_OVER_SIZED;
	if (gspca_dev->pixfmt.width == 640) {
		data[1] = MT9M111_RMB_ROW_SKIP_2X |
			  MT9M111_RMB_COLUMN_SKIP_2X |
			  (hflip << 1) | vflip;
	} else {
		data[1] = MT9M111_RMB_ROW_SKIP_4X |
			  MT9M111_RMB_COLUMN_SKIP_4X |
			  (hflip << 1) | vflip;
	}
	err = m5602_write_sensor(sd, MT9M111_SC_R_MODE_CONTEXT_B,
					data, 2);
	return err;
}