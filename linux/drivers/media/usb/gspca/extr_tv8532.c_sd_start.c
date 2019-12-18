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
struct sd {scalar_t__ packet; } ;
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {scalar_t__ empty_packet; scalar_t__ curr_mode; TYPE_2__ cam; } ;
struct TYPE_3__ {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  R0C_AD_WIDTHL ; 
 int /*<<< orphan*/  R0D_AD_WIDTHH ; 
 int /*<<< orphan*/  R28_QUANT ; 
 int /*<<< orphan*/  R29_LINE ; 
 int /*<<< orphan*/  R2C_POLARITY ; 
 int /*<<< orphan*/  R2D_POINT ; 
 int /*<<< orphan*/  R2E_POINTH ; 
 int /*<<< orphan*/  R2F_POINTB ; 
 int /*<<< orphan*/  R30_POINTBH ; 
 int /*<<< orphan*/  R31_UPD ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tv_8532_setReg (struct gspca_dev*) ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	reg_w1(gspca_dev, R0C_AD_WIDTHL, 0xe8);		/* 0x20; 0x0c */
	reg_w1(gspca_dev, R0D_AD_WIDTHH, 0x03);

	/************************************************/
	reg_w1(gspca_dev, R28_QUANT, 0x90);
					/* 0x72 compressed mode 0x28 */
	if (gspca_dev->cam.cam_mode[(int) gspca_dev->curr_mode].priv) {
		/* 176x144 */
		reg_w1(gspca_dev, R29_LINE, 0x41);
					/* CIF - 2 lines/packet */
	} else {
		/* 352x288 */
		reg_w1(gspca_dev, R29_LINE, 0x81);
					/* CIF - 2 lines/packet */
	}
	/************************************************/
	reg_w1(gspca_dev, R2C_POLARITY, 0x10);		/* slow clock */
	reg_w1(gspca_dev, R2D_POINT, 0x14);
	reg_w1(gspca_dev, R2E_POINTH, 0x01);
	reg_w1(gspca_dev, R2F_POINTB, 0x12);
	reg_w1(gspca_dev, R30_POINTBH, 0x01);

	tv_8532_setReg(gspca_dev);

	/************************************************/
	reg_w1(gspca_dev, R31_UPD, 0x01);	/* update registers */
	msleep(200);
	reg_w1(gspca_dev, R31_UPD, 0x00);	/* end update */

	gspca_dev->empty_packet = 0;		/* check the empty packets */
	sd->packet = 0;				/* ignore the first packets */

	return 0;
}