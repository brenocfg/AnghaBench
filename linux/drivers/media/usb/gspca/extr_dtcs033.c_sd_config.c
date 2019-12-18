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
struct usb_device_id {int dummy; } ;
struct TYPE_2__ {int bulk; int bulk_nurbs; int bulk_size; int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {TYPE_1__ cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int DT_COLS ; 
 int /*<<< orphan*/  dtcs033_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		const struct usb_device_id *id)
{
	gspca_dev->cam.cam_mode = dtcs033_mode;
	gspca_dev->cam.nmodes = ARRAY_SIZE(dtcs033_mode);

	gspca_dev->cam.bulk = 1;
	gspca_dev->cam.bulk_nurbs = 1;
	gspca_dev->cam.bulk_size = DT_COLS*512;

	return 0;
}