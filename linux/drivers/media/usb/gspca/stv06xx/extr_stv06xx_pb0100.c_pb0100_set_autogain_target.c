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
struct sd {int dummy; } ;
struct TYPE_2__ {int width; int height; } ;
struct gspca_dev {TYPE_1__ pixfmt; } ;
typedef  int __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  PB_R21 ; 
 int /*<<< orphan*/  PB_R22 ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int,int) ; 
 int stv06xx_write_sensor (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pb0100_set_autogain_target(struct gspca_dev *gspca_dev, __s32 val)
{
	int err, totalpixels, brightpixels, darkpixels;
	struct sd *sd = (struct sd *) gspca_dev;

	/* Number of pixels counted by the sensor when subsampling the pixels.
	 * Slightly larger than the real value to avoid oscillation */
	totalpixels = gspca_dev->pixfmt.width * gspca_dev->pixfmt.height;
	totalpixels = totalpixels/(8*8) + totalpixels/(64*64);

	brightpixels = (totalpixels * val) >> 8;
	darkpixels   = totalpixels - brightpixels;
	err = stv06xx_write_sensor(sd, PB_R21, brightpixels);
	if (!err)
		err = stv06xx_write_sensor(sd, PB_R22, darkpixels);

	gspca_dbg(gspca_dev, D_CONF, "Set autogain target to %d, status: %d\n",
		  val, err);

	return err;
}