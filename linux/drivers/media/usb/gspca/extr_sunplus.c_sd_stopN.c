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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AiptekMiniPenCam13 ; 
#define  BRIDGE_SPCA504 129 
#define  BRIDGE_SPCA504C 128 
 int /*<<< orphan*/  reg_w_riv (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  spca504A_acknowledged_command (struct gspca_dev*,int,int,int,int,int) ; 
 int /*<<< orphan*/  spca504B_PollingDataReady (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca504B_WaitCmdStatus (struct gspca_dev*) ; 
 int /*<<< orphan*/  spca504_acknowledged_command (struct gspca_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->bridge) {
	default:
/*	case BRIDGE_SPCA533: */
/*	case BRIDGE_SPCA536: */
/*	case BRIDGE_SPCA504B: */
		reg_w_riv(gspca_dev, 0x31, 0, 0);
		spca504B_WaitCmdStatus(gspca_dev);
		spca504B_PollingDataReady(gspca_dev);
		break;
	case BRIDGE_SPCA504:
	case BRIDGE_SPCA504C:
		reg_w_riv(gspca_dev, 0x00, 0x2000, 0x0000);

		if (sd->subtype == AiptekMiniPenCam13) {
			/* spca504a aiptek */
/*			spca504A_acknowledged_command(gspca_dev, 0x08,
							 6, 0, 0x86, 1); */
			spca504A_acknowledged_command(gspca_dev, 0x24,
							0x00, 0x00, 0x9d, 1);
			spca504A_acknowledged_command(gspca_dev, 0x01,
							0x0f, 0x00, 0xff, 1);
		} else {
			spca504_acknowledged_command(gspca_dev, 0x24, 0, 0);
			reg_w_riv(gspca_dev, 0x01, 0x000f, 0x0000);
		}
		break;
	}
}