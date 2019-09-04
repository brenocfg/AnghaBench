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
typedef  int /*<<< orphan*/  u8 ;
struct sd {size_t webcam; scalar_t__ exp_too_low_cnt; scalar_t__ exp_too_high_cnt; } ;
struct TYPE_2__ {int width; } ;
struct gspca_dev {int usb_err; TYPE_1__ pixfmt; } ;

/* Variables and functions */
#define  Kr651us 130 
#define  P35u 129 
#define  Proscope 128 
 int /*<<< orphan*/  const* kr651_start_2 ; 
 int /*<<< orphan*/  const* kr651_start_qvga ; 
 int /*<<< orphan*/  const* kr651_start_vga ; 
 int /*<<< orphan*/  const* nw801_start_2 ; 
 int /*<<< orphan*/  const* nw801_start_qvga ; 
 int /*<<< orphan*/  const* nw801_start_vga ; 
 int /*<<< orphan*/  const* proscope_start_2 ; 
 int /*<<< orphan*/  const* proscope_start_qvga ; 
 int /*<<< orphan*/  const* proscope_start_vga ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ ** webcam_start ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	const u8 *cmd;

	cmd = webcam_start[sd->webcam];
	reg_w_buf(gspca_dev, cmd);
	switch (sd->webcam) {
	case P35u:
		if (gspca_dev->pixfmt.width == 320)
			reg_w_buf(gspca_dev, nw801_start_qvga);
		else
			reg_w_buf(gspca_dev, nw801_start_vga);
		reg_w_buf(gspca_dev, nw801_start_2);
		break;
	case Kr651us:
		if (gspca_dev->pixfmt.width == 320)
			reg_w_buf(gspca_dev, kr651_start_qvga);
		else
			reg_w_buf(gspca_dev, kr651_start_vga);
		reg_w_buf(gspca_dev, kr651_start_2);
		break;
	case Proscope:
		if (gspca_dev->pixfmt.width == 320)
			reg_w_buf(gspca_dev, proscope_start_qvga);
		else
			reg_w_buf(gspca_dev, proscope_start_vga);
		reg_w_buf(gspca_dev, proscope_start_2);
		break;
	}

	sd->exp_too_high_cnt = 0;
	sd->exp_too_low_cnt = 0;
	return gspca_dev->usb_err;
}