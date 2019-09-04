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
struct sd {scalar_t__ ag_cnt; } ;
struct gspca_dev {int* usb_buf; } ;
typedef  int __u8 ;

/* Variables and functions */
 scalar_t__ AG_CNT_START ; 
 int BLIMIT (int) ; 
 int /*<<< orphan*/  D_FRAM ; 
 int /*<<< orphan*/  ET_LUMA_CENTER ; 
 int Et_getgainG (struct gspca_dev*) ; 
 int /*<<< orphan*/  Et_setgainG (struct gspca_dev*,int) ; 
 int LIMIT (int) ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void do_autogain(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	__u8 luma;
	__u8 luma_mean = 128;
	__u8 luma_delta = 20;
	__u8 spring = 4;
	int Gbright;
	__u8 r, g, b;

	if (sd->ag_cnt < 0)
		return;
	if (--sd->ag_cnt >= 0)
		return;
	sd->ag_cnt = AG_CNT_START;

	Gbright = Et_getgainG(gspca_dev);
	reg_r(gspca_dev, ET_LUMA_CENTER, 4);
	g = (gspca_dev->usb_buf[0] + gspca_dev->usb_buf[3]) >> 1;
	r = gspca_dev->usb_buf[1];
	b = gspca_dev->usb_buf[2];
	r = ((r << 8) - (r << 4) - (r << 3)) >> 10;
	b = ((b << 7) >> 10);
	g = ((g << 9) + (g << 7) + (g << 5)) >> 10;
	luma = LIMIT(r + g + b);
	gspca_dbg(gspca_dev, D_FRAM, "Etoms luma G %d\n", luma);
	if (luma < luma_mean - luma_delta || luma > luma_mean + luma_delta) {
		Gbright += (luma_mean - luma) >> spring;
		Gbright = BLIMIT(Gbright);
		gspca_dbg(gspca_dev, D_FRAM, "Etoms Gbright %d\n", Gbright);
		Et_setgainG(gspca_dev, (__u8) Gbright);
	}
}