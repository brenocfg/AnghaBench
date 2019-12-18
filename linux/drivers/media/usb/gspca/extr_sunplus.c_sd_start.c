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
struct sd {int bridge; int /*<<< orphan*/  autogain; int /*<<< orphan*/  subtype; int /*<<< orphan*/  jpeg_hdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct gspca_dev {int usb_err; TYPE_1__ pixfmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AiptekMiniPenCam13 ; 
#define  BRIDGE_SPCA504 132 
 int BRIDGE_SPCA504B ; 
#define  BRIDGE_SPCA504C 131 
 int /*<<< orphan*/  LogitechClickSmart420 ; 
#define  LogitechClickSmart820 130 
#define  MegaImageVI 129 
#define  MegapixV4 128 
 int /*<<< orphan*/  QUALITY ; 
 int /*<<< orphan*/  init_ctl_reg (struct gspca_dev*) ; 
 int /*<<< orphan*/  jpeg_define (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jpeg_set_qual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w_riv (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  spca504A_acknowledged_command (struct gspca_dev*,int,int,int,int,int) ; 
 int /*<<< orphan*/  spca504A_clicksmart420_init_data ; 
 int /*<<< orphan*/  spca504B_PollingDataReady (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca504B_SetSizeType (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca504B_WaitCmdStatus (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca504B_setQtable (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca504_acknowledged_command (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  spca504_pccam600_init_data ; 
 int /*<<< orphan*/  spca504_read_info (struct gspca_dev*) ; 
 int /*<<< orphan*/  write_vector (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int enable;

	/* create the JPEG header */
	jpeg_define(sd->jpeg_hdr, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x22);		/* JPEG 411 */
	jpeg_set_qual(sd->jpeg_hdr, QUALITY);

	if (sd->bridge == BRIDGE_SPCA504B)
		spca504B_setQtable(gspca_dev);
	spca504B_SetSizeType(gspca_dev);
	switch (sd->bridge) {
	default:
/*	case BRIDGE_SPCA504B: */
/*	case BRIDGE_SPCA533: */
/*	case BRIDGE_SPCA536: */
		switch (sd->subtype) {
		case MegapixV4:
		case LogitechClickSmart820:
		case MegaImageVI:
			reg_w_riv(gspca_dev, 0xf0, 0, 0);
			spca504B_WaitCmdStatus(gspca_dev);
			reg_r(gspca_dev, 0xf0, 4, 0);
			spca504B_WaitCmdStatus(gspca_dev);
			break;
		default:
			reg_w_riv(gspca_dev, 0x31, 0x0004, 0x00);
			spca504B_WaitCmdStatus(gspca_dev);
			spca504B_PollingDataReady(gspca_dev);
			break;
		}
		break;
	case BRIDGE_SPCA504:
		if (sd->subtype == AiptekMiniPenCam13) {
			spca504_read_info(gspca_dev);

			/* Set AE AWB Banding Type 3-> 50Hz 2-> 60Hz */
			spca504A_acknowledged_command(gspca_dev, 0x24,
							8, 3, 0x9e, 1);
			/* Twice sequential need status 0xff->0x9e->0x9d */
			spca504A_acknowledged_command(gspca_dev, 0x24,
							8, 3, 0x9e, 0);
			spca504A_acknowledged_command(gspca_dev, 0x24,
							0, 0, 0x9d, 1);
		} else {
			spca504_acknowledged_command(gspca_dev, 0x24, 8, 3);
			spca504_read_info(gspca_dev);
			spca504_acknowledged_command(gspca_dev, 0x24, 8, 3);
			spca504_acknowledged_command(gspca_dev, 0x24, 0, 0);
		}
		spca504B_SetSizeType(gspca_dev);
		reg_w_riv(gspca_dev, 0x00, 0x270c, 0x05);
							/* L92 sno1t.txt */
		reg_w_riv(gspca_dev, 0x00, 0x2310, 0x05);
		break;
	case BRIDGE_SPCA504C:
		if (sd->subtype == LogitechClickSmart420) {
			write_vector(gspca_dev,
				spca504A_clicksmart420_init_data,
				ARRAY_SIZE(spca504A_clicksmart420_init_data));
		} else {
			write_vector(gspca_dev, spca504_pccam600_init_data,
				ARRAY_SIZE(spca504_pccam600_init_data));
		}
		enable = (sd->autogain ? 0x04 : 0x01);
		reg_w_riv(gspca_dev, 0x0c, 0x0000, enable);
							/* auto exposure */
		reg_w_riv(gspca_dev, 0xb0, 0x0000, enable);
							/* auto whiteness */

		/* set default exposure compensation and whiteness balance */
		reg_w_riv(gspca_dev, 0x30, 0x0001, 800);	/* ~ 20 fps */
		reg_w_riv(gspca_dev, 0x30, 0x0002, 1600);
		spca504B_SetSizeType(gspca_dev);
		break;
	}
	init_ctl_reg(gspca_dev);
	return gspca_dev->usb_err;
}