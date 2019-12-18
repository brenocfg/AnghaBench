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
typedef  int u16 ;
struct TYPE_2__ {unsigned int width; } ;
struct gspca_dev {int /*<<< orphan*/  usb_err; TYPE_1__ pixfmt; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  REG_COARSE_INTEGRATION_TIME_ ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*,unsigned int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev, s32 val)
{
	u16 value;
	unsigned int w = gspca_dev->pixfmt.width;

	if (w == 800)
		value = val * 5;
	else if (w == 1600)
		value = val * 3;
	else if (w == 3264)
		value = val * 3 / 2;
	else {
		gspca_err(gspca_dev, "Invalid width %u\n", w);
		gspca_dev->usb_err = -EINVAL;
		return;
	}
	gspca_dbg(gspca_dev, D_STREAM, "exposure: 0x%04X ms\n\n", value);
	/* Wonder if there's a good reason for sending it twice */
	/* probably not but leave it in because...why not */
	reg_w(gspca_dev, value, REG_COARSE_INTEGRATION_TIME_);
	reg_w(gspca_dev, value, REG_COARSE_INTEGRATION_TIME_);
}