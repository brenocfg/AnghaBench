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
struct TYPE_4__ {TYPE_1__* cam_mode; } ;
struct gspca_dev {int* usb_buf; scalar_t__ curr_mode; TYPE_2__ cam; } ;
typedef  int __u8 ;
struct TYPE_3__ {int priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,int,int) ; 

__attribute__((used)) static int sd_start_12a(struct gspca_dev *gspca_dev)
{
	int mode;
	static const __u8 Reg8391[8] =
		{0x92, 0x30, 0x20, 0x00, 0x0c, 0x00, 0x00, 0x00};

	mode = gspca_dev->cam.cam_mode[(int) gspca_dev->curr_mode].priv;
	if (mode <= 1) {
		/* Use compression on 320x240 and above */
		reg_w_val(gspca_dev, 0x8500, 0x10 | mode);
	} else {
		/* I couldn't get the compression to work below 320x240
		 * Fortunately at these resolutions the bandwidth
		 * is sufficient to push raw frames at ~20fps */
		reg_w_val(gspca_dev, 0x8500, mode);
	}		/* -- qq@kuku.eu.org */

	gspca_dev->usb_buf[0] = 0xaa;
	gspca_dev->usb_buf[1] = 0x00;
	reg_w_buf(gspca_dev, 0x8307, 2);
	/* clock - lower 0x8X values lead to fps > 30 */
	reg_w_val(gspca_dev, 0x8700, 0x8a);
					/* 0x8f 0x85 0x27 clock */
	reg_w_val(gspca_dev, 0x8112, 0x1e | 0x20);
	reg_w_val(gspca_dev, 0x850b, 0x03);
	memcpy(gspca_dev->usb_buf, Reg8391, 8);
	reg_w_buf(gspca_dev, 0x8391, 8);
	reg_w_buf(gspca_dev, 0x8390, 8);

	/* Led ON (bit 3 -> 0 */
	reg_w_val(gspca_dev, 0x8114, 0x00);
	return 0;
}