#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sd {size_t sensor; int flags; int reg18; int reg01; int reg17; scalar_t__ short_mark; scalar_t__ nchg; scalar_t__ npkt; scalar_t__ pktsz; int /*<<< orphan*/  jpeg_hdr; } ;
struct TYPE_5__ {TYPE_1__* cam_mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct gspca_dev {size_t curr_mode; int usb_err; TYPE_2__ cam; scalar_t__ audio; TYPE_3__ pixfmt; } ;
struct TYPE_4__ {int priv; } ;

/* Variables and functions */
 int DEF_EN ; 
 int F_PDN_INV ; 
 int MCK_SIZE_MASK ; 
 int SCL_SEL_OD ; 
#define  SENSOR_ADCM1700 142 
#define  SENSOR_GC0307 141 
#define  SENSOR_HV7131R 140 
#define  SENSOR_MI0360 139 
#define  SENSOR_MI0360B 138 
#define  SENSOR_MO4000 137 
#define  SENSOR_MT9V111 136 
#define  SENSOR_OM6802 135 
#define  SENSOR_OV7630 134 
#define  SENSOR_OV7648 133 
#define  SENSOR_OV7660 132 
#define  SENSOR_PO1030 131 
#define  SENSOR_PO2030N 130 
#define  SENSOR_SOI768 129 
#define  SENSOR_SP80708 128 
 int SEN_CLK_EN ; 
 int SYS_SEL_48M ; 
 int S_PDN_INV ; 
 int S_PWR_DN ; 
 int V_TX_EN ; 
 int** adcm1700_sensor_param1 ; 
 int** gc0307_sensor_param1 ; 
 int /*<<< orphan*/  hv7131r_probe (struct gspca_dev*) ; 
 int /*<<< orphan*/  i2c_w8 (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_w_seq (struct gspca_dev*,int const**) ; 
 int /*<<< orphan*/  jpeg_define (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int** mi0360b_sensor_param1 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int** mt9v111_sensor_param1 ; 
 int /*<<< orphan*/ * om6802_init0 ; 
 int** om6802_sensor_param1 ; 
 int** ov7630_sensor_param1 ; 
 int** ov7648_sensor_param1 ; 
 int** ov7660_sensor_param1 ; 
 int** po1030_sensor_param1 ; 
 int** po2030n_sensor_param1 ; 
 int const* reg84 ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int const*,int) ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int,int const) ; 
 int const*** sensor_init ; 
 int /*<<< orphan*/  setgamma (struct gspca_dev*) ; 
 int /*<<< orphan*/  setjpegqual (struct gspca_dev*) ; 
 int /*<<< orphan*/  setsharpness (struct gspca_dev*) ; 
 int** sn_tb ; 
 int** soi768_sensor_param1 ; 
 int** sp80708_sensor_param1 ; 

__attribute__((used)) static int sd_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i;
	u8 reg01, reg17;
	u8 reg0102[2];
	const u8 *sn9c1xx;
	const u8 (*init)[8];
	const u8 *reg9a;
	int mode;
	static const u8 reg9a_def[] =
		{0x00, 0x40, 0x20, 0x00, 0x00, 0x00};
	static const u8 reg9a_spec[] =
		{0x00, 0x40, 0x38, 0x30, 0x00, 0x20};
	static const u8 regd4[] = {0x60, 0x00, 0x00};
	static const u8 C0[] = { 0x2d, 0x2d, 0x3a, 0x05, 0x04, 0x3f };
	static const u8 CA[] = { 0x28, 0xd8, 0x14, 0xec };
	static const u8 CA_adcm1700[] =
				{ 0x14, 0xec, 0x0a, 0xf6 };
	static const u8 CA_po2030n[] =
				{ 0x1e, 0xe2, 0x14, 0xec };
	static const u8 CE[] = { 0x32, 0xdd, 0x2d, 0xdd };	/* MI0360 */
	static const u8 CE_gc0307[] =
				{ 0x32, 0xce, 0x2d, 0xd3 };
	static const u8 CE_ov76xx[] =
				{ 0x32, 0xdd, 0x32, 0xdd };
	static const u8 CE_po2030n[] =
				{ 0x14, 0xe7, 0x1e, 0xdd };

	/* create the JPEG header */
	jpeg_define(sd->jpeg_hdr, gspca_dev->pixfmt.height,
			gspca_dev->pixfmt.width,
			0x21);		/* JPEG 422 */

	/* initialize the bridge */
	sn9c1xx = sn_tb[sd->sensor];

	/* sensor clock already enabled in sd_init */
	/* reg_w1(gspca_dev, 0xf1, 0x00); */
	reg01 = sn9c1xx[1];
	if (sd->flags & F_PDN_INV)
		reg01 ^= S_PDN_INV;		/* power down inverted */
	reg_w1(gspca_dev, 0x01, reg01);

	/* configure gpio */
	reg0102[0] = reg01;
	reg0102[1] = sn9c1xx[2];
	if (gspca_dev->audio)
		reg0102[1] |= 0x04;	/* keep the audio connection */
	reg_w(gspca_dev, 0x01, reg0102, 2);
	reg_w(gspca_dev, 0x08, &sn9c1xx[8], 2);
	reg_w(gspca_dev, 0x17, &sn9c1xx[0x17], 5);
	switch (sd->sensor) {
	case SENSOR_GC0307:
	case SENSOR_OV7660:
	case SENSOR_PO1030:
	case SENSOR_PO2030N:
	case SENSOR_SOI768:
	case SENSOR_SP80708:
		reg9a = reg9a_spec;
		break;
	default:
		reg9a = reg9a_def;
		break;
	}
	reg_w(gspca_dev, 0x9a, reg9a, 6);

	reg_w(gspca_dev, 0xd4, regd4, sizeof regd4);

	reg_w(gspca_dev, 0x03, &sn9c1xx[3], 0x0f);

	reg17 = sn9c1xx[0x17];
	switch (sd->sensor) {
	case SENSOR_GC0307:
		msleep(50);		/*fixme: is it useful? */
		break;
	case SENSOR_OM6802:
		msleep(10);
		reg_w1(gspca_dev, 0x02, 0x73);
		reg17 |= SEN_CLK_EN;
		reg_w1(gspca_dev, 0x17, reg17);
		reg_w1(gspca_dev, 0x01, 0x22);
		msleep(100);
		reg01 = SCL_SEL_OD | S_PDN_INV;
		reg17 &= ~MCK_SIZE_MASK;
		reg17 |= 0x04;		/* clock / 4 */
		break;
	}
	reg01 |= SYS_SEL_48M;
	reg_w1(gspca_dev, 0x01, reg01);
	reg17 |= SEN_CLK_EN;
	reg_w1(gspca_dev, 0x17, reg17);
	reg01 &= ~S_PWR_DN;		/* sensor power on */
	reg_w1(gspca_dev, 0x01, reg01);
	reg01 &= ~SCL_SEL_OD;		/* remove open-drain mode */
	reg_w1(gspca_dev, 0x01, reg01);

	switch (sd->sensor) {
	case SENSOR_HV7131R:
		hv7131r_probe(gspca_dev);	/*fixme: is it useful? */
		break;
	case SENSOR_OM6802:
		msleep(10);
		reg_w1(gspca_dev, 0x01, reg01);
		i2c_w8(gspca_dev, om6802_init0[0]);
		i2c_w8(gspca_dev, om6802_init0[1]);
		msleep(15);
		reg_w1(gspca_dev, 0x02, 0x71);
		msleep(150);
		break;
	case SENSOR_SP80708:
		msleep(100);
		reg_w1(gspca_dev, 0x02, 0x62);
		break;
	}

	/* initialize the sensor */
	i2c_w_seq(gspca_dev, sensor_init[sd->sensor]);

	reg_w1(gspca_dev, 0x15, sn9c1xx[0x15]);
	reg_w1(gspca_dev, 0x16, sn9c1xx[0x16]);
	reg_w1(gspca_dev, 0x12, sn9c1xx[0x12]);
	reg_w1(gspca_dev, 0x13, sn9c1xx[0x13]);
	reg_w1(gspca_dev, 0x18, sn9c1xx[0x18]);
	if (sd->sensor == SENSOR_ADCM1700) {
		reg_w1(gspca_dev, 0xd2, 0x3a);	/* AE_H_SIZE = 116 */
		reg_w1(gspca_dev, 0xd3, 0x30);	/* AE_V_SIZE = 96 */
	} else {
		reg_w1(gspca_dev, 0xd2, 0x6a);	/* AE_H_SIZE = 212 */
		reg_w1(gspca_dev, 0xd3, 0x50);	/* AE_V_SIZE = 160 */
	}
	reg_w1(gspca_dev, 0xc6, 0x00);
	reg_w1(gspca_dev, 0xc7, 0x00);
	if (sd->sensor == SENSOR_ADCM1700) {
		reg_w1(gspca_dev, 0xc8, 0x2c);	/* AW_H_STOP = 352 */
		reg_w1(gspca_dev, 0xc9, 0x24);	/* AW_V_STOP = 288 */
	} else {
		reg_w1(gspca_dev, 0xc8, 0x50);	/* AW_H_STOP = 640 */
		reg_w1(gspca_dev, 0xc9, 0x3c);	/* AW_V_STOP = 480 */
	}
	reg_w1(gspca_dev, 0x18, sn9c1xx[0x18]);
	switch (sd->sensor) {
	case SENSOR_OM6802:
/*	case SENSOR_OV7648:		* fixme: sometimes */
		break;
	default:
		reg17 |= DEF_EN;
		break;
	}
	reg_w1(gspca_dev, 0x17, reg17);

	reg_w1(gspca_dev, 0x05, 0x00);		/* red */
	reg_w1(gspca_dev, 0x07, 0x00);		/* green */
	reg_w1(gspca_dev, 0x06, 0x00);		/* blue */
	reg_w1(gspca_dev, 0x14, sn9c1xx[0x14]);

	setgamma(gspca_dev);

/*fixme: 8 times with all zeroes and 1 or 2 times with normal values */
	for (i = 0; i < 8; i++)
		reg_w(gspca_dev, 0x84, reg84, sizeof reg84);
	switch (sd->sensor) {
	case SENSOR_ADCM1700:
	case SENSOR_OV7660:
	case SENSOR_SP80708:
		reg_w1(gspca_dev, 0x9a, 0x05);
		break;
	case SENSOR_GC0307:
	case SENSOR_MT9V111:
	case SENSOR_MI0360B:
		reg_w1(gspca_dev, 0x9a, 0x07);
		break;
	case SENSOR_OV7630:
	case SENSOR_OV7648:
		reg_w1(gspca_dev, 0x9a, 0x0a);
		break;
	case SENSOR_PO2030N:
	case SENSOR_SOI768:
		reg_w1(gspca_dev, 0x9a, 0x06);
		break;
	default:
		reg_w1(gspca_dev, 0x9a, 0x08);
		break;
	}
	setsharpness(gspca_dev);

	reg_w(gspca_dev, 0x84, reg84, sizeof reg84);
	reg_w1(gspca_dev, 0x05, 0x20);		/* red */
	reg_w1(gspca_dev, 0x07, 0x20);		/* green */
	reg_w1(gspca_dev, 0x06, 0x20);		/* blue */

	init = NULL;
	mode = gspca_dev->cam.cam_mode[gspca_dev->curr_mode].priv;
	reg01 |= SYS_SEL_48M | V_TX_EN;
	reg17 &= ~MCK_SIZE_MASK;
	reg17 |= 0x02;			/* clock / 2 */
	switch (sd->sensor) {
	case SENSOR_ADCM1700:
		init = adcm1700_sensor_param1;
		break;
	case SENSOR_GC0307:
		init = gc0307_sensor_param1;
		break;
	case SENSOR_HV7131R:
	case SENSOR_MI0360:
		if (!mode)
			reg01 &= ~SYS_SEL_48M;	/* 640x480: clk 24Mhz */
		reg17 &= ~MCK_SIZE_MASK;
		reg17 |= 0x01;			/* clock / 1 */
		break;
	case SENSOR_MI0360B:
		init = mi0360b_sensor_param1;
		break;
	case SENSOR_MO4000:
		if (mode) {			/* if 320x240 */
			reg01 &= ~SYS_SEL_48M;	/* clk 24Mz */
			reg17 &= ~MCK_SIZE_MASK;
			reg17 |= 0x01;		/* clock / 1 */
		}
		break;
	case SENSOR_MT9V111:
		init = mt9v111_sensor_param1;
		break;
	case SENSOR_OM6802:
		init = om6802_sensor_param1;
		if (!mode) {			/* if 640x480 */
			reg17 &= ~MCK_SIZE_MASK;
			reg17 |= 0x04;		/* clock / 4 */
		} else {
			reg01 &= ~SYS_SEL_48M;	/* clk 24Mz */
			reg17 &= ~MCK_SIZE_MASK;
			reg17 |= 0x02;		/* clock / 2 */
		}
		break;
	case SENSOR_OV7630:
		init = ov7630_sensor_param1;
		break;
	case SENSOR_OV7648:
		init = ov7648_sensor_param1;
		reg17 &= ~MCK_SIZE_MASK;
		reg17 |= 0x01;			/* clock / 1 */
		break;
	case SENSOR_OV7660:
		init = ov7660_sensor_param1;
		break;
	case SENSOR_PO1030:
		init = po1030_sensor_param1;
		break;
	case SENSOR_PO2030N:
		init = po2030n_sensor_param1;
		break;
	case SENSOR_SOI768:
		init = soi768_sensor_param1;
		break;
	case SENSOR_SP80708:
		init = sp80708_sensor_param1;
		break;
	}

	/* more sensor initialization - param1 */
	if (init != NULL) {
		i2c_w_seq(gspca_dev, init);
/*		init = NULL; */
	}

	reg_w(gspca_dev, 0xc0, C0, 6);
	switch (sd->sensor) {
	case SENSOR_ADCM1700:
	case SENSOR_GC0307:
	case SENSOR_SOI768:
		reg_w(gspca_dev, 0xca, CA_adcm1700, 4);
		break;
	case SENSOR_PO2030N:
		reg_w(gspca_dev, 0xca, CA_po2030n, 4);
		break;
	default:
		reg_w(gspca_dev, 0xca, CA, 4);
		break;
	}
	switch (sd->sensor) {
	case SENSOR_ADCM1700:
	case SENSOR_OV7630:
	case SENSOR_OV7648:
	case SENSOR_OV7660:
	case SENSOR_SOI768:
		reg_w(gspca_dev, 0xce, CE_ov76xx, 4);
		break;
	case SENSOR_GC0307:
		reg_w(gspca_dev, 0xce, CE_gc0307, 4);
		break;
	case SENSOR_PO2030N:
		reg_w(gspca_dev, 0xce, CE_po2030n, 4);
		break;
	default:
		reg_w(gspca_dev, 0xce, CE, 4);
					/* ?? {0x1e, 0xdd, 0x2d, 0xe7} */
		break;
	}

	/* here change size mode 0 -> VGA; 1 -> CIF */
	sd->reg18 = sn9c1xx[0x18] | (mode << 4) | 0x40;
	reg_w1(gspca_dev, 0x18, sd->reg18);
	setjpegqual(gspca_dev);

	reg_w1(gspca_dev, 0x17, reg17);
	reg_w1(gspca_dev, 0x01, reg01);
	sd->reg01 = reg01;
	sd->reg17 = reg17;

	sd->pktsz = sd->npkt = 0;
	sd->nchg = sd->short_mark = 0;

	return gspca_dev->usb_err;
}