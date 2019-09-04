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
struct sd {int model; scalar_t__ sof_read; } ;
struct gspca_dev {TYPE_1__** urb; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  pipe; } ;

/* Variables and functions */
#define  CIT_IBM_NETCAM_PRO 133 
#define  CIT_MODEL0 132 
#define  CIT_MODEL1 131 
#define  CIT_MODEL2 130 
#define  CIT_MODEL3 129 
#define  CIT_MODEL4 128 
 int /*<<< orphan*/  cit_write_reg (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  usb_clear_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cit_restart_stream(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->model) {
	case CIT_MODEL0:
	case CIT_MODEL1:
		cit_write_reg(gspca_dev, 0x0001, 0x0114);
		/* Fall through */
	case CIT_MODEL2:
	case CIT_MODEL4:
		cit_write_reg(gspca_dev, 0x00c0, 0x010c); /* Go! */
		usb_clear_halt(gspca_dev->dev, gspca_dev->urb[0]->pipe);
		break;
	case CIT_MODEL3:
	case CIT_IBM_NETCAM_PRO:
		cit_write_reg(gspca_dev, 0x0001, 0x0114);
		cit_write_reg(gspca_dev, 0x00c0, 0x010c); /* Go! */
		usb_clear_halt(gspca_dev->dev, gspca_dev->urb[0]->pipe);
		/* Clear button events from while we were not streaming */
		cit_write_reg(gspca_dev, 0x0001, 0x0113);
		break;
	}

	sd->sof_read = 0;

	return 0;
}