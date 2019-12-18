#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sd {int subtype; } ;
struct TYPE_3__ {TYPE_2__* cam_mode; } ;
struct gspca_dev {scalar_t__ curr_mode; TYPE_1__ cam; } ;
struct TYPE_4__ {int priv; } ;

/* Variables and functions */
#define  Arowana300KCMOSCamera 131 
#define  MystFromOriUnknownCamera 130 
 int /*<<< orphan*/  SPCA501_REG_CTLRL ; 
 int /*<<< orphan*/  SPCA50X_REG_USB ; 
#define  SmileIntlCamera 129 
#define  ThreeComHomeConnectLite 128 
 int /*<<< orphan*/  reg_write (struct gspca_dev*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spca501_3com_open_data ; 
 int /*<<< orphan*/  spca501_open_data ; 
 int /*<<< orphan*/  spca501c_arowana_open_data ; 
 int /*<<< orphan*/  spca501c_mysterious_init_data ; 
 int /*<<< orphan*/  write_vector (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int mode;

	switch (sd->subtype) {
	case ThreeComHomeConnectLite:
		/* Special handling for 3com data */
		write_vector(gspca_dev, spca501_3com_open_data);
		break;
	case Arowana300KCMOSCamera:
	case SmileIntlCamera:
		/* Arowana 300k CMOS Camera data */
		write_vector(gspca_dev, spca501c_arowana_open_data);
		break;
	case MystFromOriUnknownCamera:
		/* Unknown CMOS Camera data */
		write_vector(gspca_dev, spca501c_mysterious_init_data);
		break;
	default:
		/* Generic 501 open data */
		write_vector(gspca_dev, spca501_open_data);
	}

	/* memorize the wanted pixel format */
	mode = gspca_dev->cam.cam_mode[(int) gspca_dev->curr_mode].priv;

	/* Enable ISO packet machine CTRL reg=2,
	 * index=1 bitmask=0x2 (bit ordinal 1) */
	reg_write(gspca_dev, SPCA50X_REG_USB, 0x6, 0x94);
	switch (mode) {
	case 0: /* 640x480 */
		reg_write(gspca_dev, SPCA50X_REG_USB, 0x07, 0x004a);
		break;
	case 1: /* 320x240 */
		reg_write(gspca_dev, SPCA50X_REG_USB, 0x07, 0x104a);
		break;
	default:
/*	case 2:  * 160x120 */
		reg_write(gspca_dev, SPCA50X_REG_USB, 0x07, 0x204a);
		break;
	}
	reg_write(gspca_dev, SPCA501_REG_CTLRL, 0x01, 0x02);

	return 0;
}