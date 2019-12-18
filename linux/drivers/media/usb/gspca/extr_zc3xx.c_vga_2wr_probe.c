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
typedef  int u16 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  SENSOR_PAS202B ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int i2c_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  i2c_write (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  send_unknown (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_2wr_probe (struct gspca_dev*,int) ; 

__attribute__((used)) static int vga_2wr_probe(struct gspca_dev *gspca_dev)
{
	u16 retword;

	start_2wr_probe(gspca_dev, 0x00);	/* HV7131B */
	i2c_write(gspca_dev, 0x01, 0xaa, 0x00);
	retword = i2c_read(gspca_dev, 0x01);
	if (retword != 0)
		return 0x00;			/* HV7131B */

	start_2wr_probe(gspca_dev, 0x04);	/* CS2102 */
	i2c_write(gspca_dev, 0x01, 0xaa, 0x00);
	retword = i2c_read(gspca_dev, 0x01);
	if (retword != 0)
		return 0x04;			/* CS2102 */

	start_2wr_probe(gspca_dev, 0x06);	/* OmniVision */
	reg_w(gspca_dev, 0x08, 0x008d);
	i2c_write(gspca_dev, 0x11, 0xaa, 0x00);
	retword = i2c_read(gspca_dev, 0x11);
	if (retword != 0) {
		/* (should have returned 0xaa) --> Omnivision? */
		/* reg_r 0x10 -> 0x06 -->  */
		goto ov_check;
	}

	start_2wr_probe(gspca_dev, 0x08);	/* HDCS2020 */
	i2c_write(gspca_dev, 0x1c, 0x00, 0x00);
	i2c_write(gspca_dev, 0x15, 0xaa, 0x00);
	retword = i2c_read(gspca_dev, 0x15);
	if (retword != 0)
		return 0x08;			/* HDCS2020 */

	start_2wr_probe(gspca_dev, 0x0a);	/* PB0330 */
	i2c_write(gspca_dev, 0x07, 0xaa, 0xaa);
	retword = i2c_read(gspca_dev, 0x07);
	if (retword != 0)
		return 0x0a;			/* PB0330 */
	retword = i2c_read(gspca_dev, 0x03);
	if (retword != 0)
		return 0x0a;			/* PB0330 ?? */
	retword = i2c_read(gspca_dev, 0x04);
	if (retword != 0)
		return 0x0a;			/* PB0330 ?? */

	start_2wr_probe(gspca_dev, 0x0c);	/* ICM105A */
	i2c_write(gspca_dev, 0x01, 0x11, 0x00);
	retword = i2c_read(gspca_dev, 0x01);
	if (retword != 0)
		return 0x0c;			/* ICM105A */

	start_2wr_probe(gspca_dev, 0x0e);	/* PAS202BCB */
	reg_w(gspca_dev, 0x08, 0x008d);
	i2c_write(gspca_dev, 0x03, 0xaa, 0x00);
	msleep(50);
	retword = i2c_read(gspca_dev, 0x03);
	if (retword != 0) {
		send_unknown(gspca_dev, SENSOR_PAS202B);
		return 0x0e;			/* PAS202BCB */
	}

	start_2wr_probe(gspca_dev, 0x02);	/* TAS5130C */
	i2c_write(gspca_dev, 0x01, 0xaa, 0x00);
	retword = i2c_read(gspca_dev, 0x01);
	if (retword != 0)
		return 0x02;			/* TAS5130C */
ov_check:
	reg_r(gspca_dev, 0x0010);		/* ?? */
	reg_r(gspca_dev, 0x0010);

	reg_w(gspca_dev, 0x01, 0x0000);
	reg_w(gspca_dev, 0x01, 0x0001);
	reg_w(gspca_dev, 0x06, 0x0010);		/* OmniVision */
	reg_w(gspca_dev, 0xa1, 0x008b);
	reg_w(gspca_dev, 0x08, 0x008d);
	msleep(500);
	reg_w(gspca_dev, 0x01, 0x0012);
	i2c_write(gspca_dev, 0x12, 0x80, 0x00);	/* sensor reset */
	retword = i2c_read(gspca_dev, 0x0a) << 8;
	retword |= i2c_read(gspca_dev, 0x0b);
	gspca_dbg(gspca_dev, D_PROBE, "probe 2wr ov vga 0x%04x\n", retword);
	switch (retword) {
	case 0x7631:				/* OV7630C */
		reg_w(gspca_dev, 0x06, 0x0010);
		break;
	case 0x7620:				/* OV7620 */
	case 0x7648:				/* OV7648 */
		break;
	default:
		return -1;			/* not OmniVision */
	}
	return retword;
}