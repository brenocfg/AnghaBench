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
struct sd {int fmt; int /*<<< orphan*/ * jpeg_hdr; } ;
struct gspca_dev {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 size_t JPEG_QT0_OFFSET ; 
 size_t JPEG_QT1_OFFSET ; 
 int /*<<< orphan*/  jpeg_set_qual (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void set_quality(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	jpeg_set_qual(sd->jpeg_hdr, val);
	reg_w1(gspca_dev, 0x1061, 0x01);	/* stop transfer */
	reg_w1(gspca_dev, 0x10e0, sd->fmt | 0x20); /* write QTAB */
	reg_w(gspca_dev, 0x1100, &sd->jpeg_hdr[JPEG_QT0_OFFSET], 64);
	reg_w(gspca_dev, 0x1140, &sd->jpeg_hdr[JPEG_QT1_OFFSET], 64);
	reg_w1(gspca_dev, 0x1061, 0x03);	/* restart transfer */
	reg_w1(gspca_dev, 0x10e0, sd->fmt);
	sd->fmt ^= 0x0c;			/* invert QTAB use + write */
	reg_w1(gspca_dev, 0x10e0, sd->fmt);
}