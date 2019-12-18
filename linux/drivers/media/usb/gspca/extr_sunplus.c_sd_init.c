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
struct sd {int bridge; int /*<<< orphan*/  subtype; } ;
struct gspca_dev {int usb_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AiptekMiniPenCam13 ; 
#define  BRIDGE_SPCA504B 131 
#define  BRIDGE_SPCA504C 130 
#define  BRIDGE_SPCA533 129 
#define  BRIDGE_SPCA536 128 
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  LogitechClickSmart420 ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  qtable_creative_pccam ; 
 int /*<<< orphan*/  qtable_spca504_default ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  reg_w_1 (struct gspca_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w_riv (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  setup_qtable (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spca504A_acknowledged_command (struct gspca_dev*,int,int,int,int,int) ; 
 int /*<<< orphan*/  spca504A_clicksmart420_open_data ; 
 int /*<<< orphan*/  spca504B_PollingDataReady (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca504B_WaitCmdStatus (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca504_pccam600_open_data ; 
 int /*<<< orphan*/  spca504_read_info (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca504_wait_status (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca50x_GetFirmware (struct gspca_dev*) ; 
 int /*<<< orphan*/  write_vector (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->bridge) {
	case BRIDGE_SPCA504B:
		reg_w_riv(gspca_dev, 0x1d, 0x00, 0);
		reg_w_riv(gspca_dev, 0x00, 0x2306, 0x01);
		reg_w_riv(gspca_dev, 0x00, 0x0d04, 0x00);
		reg_w_riv(gspca_dev, 0x00, 0x2000, 0x00);
		reg_w_riv(gspca_dev, 0x00, 0x2301, 0x13);
		reg_w_riv(gspca_dev, 0x00, 0x2306, 0x00);
		/* fall through */
	case BRIDGE_SPCA533:
		spca504B_PollingDataReady(gspca_dev);
		spca50x_GetFirmware(gspca_dev);
		break;
	case BRIDGE_SPCA536:
		spca50x_GetFirmware(gspca_dev);
		reg_r(gspca_dev, 0x00, 0x5002, 1);
		reg_w_1(gspca_dev, 0x24, 0, 0, 0);
		reg_r(gspca_dev, 0x24, 0, 1);
		spca504B_PollingDataReady(gspca_dev);
		reg_w_riv(gspca_dev, 0x34, 0, 0);
		spca504B_WaitCmdStatus(gspca_dev);
		break;
	case BRIDGE_SPCA504C:	/* pccam600 */
		gspca_dbg(gspca_dev, D_STREAM, "Opening SPCA504 (PC-CAM 600)\n");
		reg_w_riv(gspca_dev, 0xe0, 0x0000, 0x0000);
		reg_w_riv(gspca_dev, 0xe0, 0x0000, 0x0001);	/* reset */
		spca504_wait_status(gspca_dev);
		if (sd->subtype == LogitechClickSmart420)
			write_vector(gspca_dev,
				spca504A_clicksmart420_open_data,
				ARRAY_SIZE(spca504A_clicksmart420_open_data));
		else
			write_vector(gspca_dev, spca504_pccam600_open_data,
				ARRAY_SIZE(spca504_pccam600_open_data));
		setup_qtable(gspca_dev, qtable_creative_pccam);
		break;
	default:
/*	case BRIDGE_SPCA504: */
		gspca_dbg(gspca_dev, D_STREAM, "Opening SPCA504\n");
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
			/******************************/
			/* spca504a aiptek */
			spca504A_acknowledged_command(gspca_dev, 0x08,
							6, 0, 0x86, 1);
/*			reg_write (dev, 0, 0x2000, 0); */
/*			reg_write (dev, 0, 0x2883, 1); */
/*			spca504A_acknowledged_command (gspca_dev, 0x08,
							6, 0, 0x86, 1); */
/*			spca504A_acknowledged_command (gspca_dev, 0x24,
							0, 0, 0x9D, 1); */
			reg_w_riv(gspca_dev, 0x00, 0x270c, 0x05);
							/* L92 sno1t.txt */
			reg_w_riv(gspca_dev, 0x00, 0x2310, 0x05);
			spca504A_acknowledged_command(gspca_dev, 0x01,
							0x0f, 0, 0xff, 0);
		}
		/* setup qtable */
		reg_w_riv(gspca_dev, 0, 0x2000, 0);
		reg_w_riv(gspca_dev, 0, 0x2883, 1);
		setup_qtable(gspca_dev, qtable_spca504_default);
		break;
	}
	return gspca_dev->usb_err;
}