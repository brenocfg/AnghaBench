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
typedef  int uint8_t ;
typedef  int u8 ;
struct helene_priv {scalar_t__ xtal; TYPE_1__* i2c; } ;
typedef  int /*<<< orphan*/  rdata ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  cdata ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ SONY_HELENE_XTAL_16000 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  helene_read_reg (struct helene_priv*,int,int*) ; 
 int /*<<< orphan*/  helene_read_regs (struct helene_priv*,int,int*,int) ; 
 int /*<<< orphan*/  helene_write_reg (struct helene_priv*,int,int) ; 
 int /*<<< orphan*/  helene_write_regs (struct helene_priv*,int,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int helene_x_pon(struct helene_priv *priv)
{
	/* RFIN matching in power save (terrestrial) = ACTIVE */
	/* RFIN matching in power save (satellite) = ACTIVE */
	u8 dataT[] = { 0x06, 0x00, 0x02, 0x00 };
	/* SAT_RF_ACTIVE = true, lnaOff = false, terrRfActive = true */
	u8 dataS[] = { 0x05, 0x06 };
	u8 cdata[] = {0x7A, 0x01};
	u8 data[20];
	u8 rdata[2];

	/* mode select */
	helene_write_reg(priv, 0x01, 0x00);

	helene_write_reg(priv, 0x67, dataT[3]);
	helene_write_reg(priv, 0x43, dataS[1]);
	helene_write_regs(priv, 0x5E, dataT, 3);
	helene_write_reg(priv, 0x0C, dataS[0]);

	/* Initial setting for internal logic block */
	helene_write_regs(priv, 0x99, cdata, sizeof(cdata));

	/* 0x81 - 0x94 */
	if (priv->xtal == SONY_HELENE_XTAL_16000)
		data[0] = 0x10; /* xtal 16 MHz */
	else
		data[0] = 0x18; /* xtal 24 MHz */
	data[1] = (uint8_t)(0x80 | (0x04 & 0x1F)); /* 4 x 25 = 100uA */
	data[2] = (uint8_t)(0x80 | (0x26 & 0x7F)); /* 38 x 0.25 = 9.5pF */
	data[3] = 0x80; /* REFOUT signal output 500mVpp */
	data[4] = 0x00; /* GPIO settings */
	data[5] = 0x00; /* GPIO settings */
	data[6] = 0xC4; /* Clock enable for internal logic block */
	data[7] = 0x40; /* Start CPU boot-up */
	data[8] = 0x10; /* For burst-write */

	/* Setting for internal RFAGC */
	data[9] = 0x00;
	data[10] = 0x45;
	data[11] = 0x75;

	data[12] = 0x07; /* Setting for analog block */

	/* Initial setting for internal analog block */
	data[13] = 0x1C;
	data[14] = 0x3F;
	data[15] = 0x02;
	data[16] = 0x10;
	data[17] = 0x20;
	data[18] = 0x0A;
	data[19] = 0x00;

	helene_write_regs(priv, 0x81, data, sizeof(data));

	/* Setting for internal RFAGC */
	helene_write_reg(priv, 0x9B, 0x00);

	msleep(20);

	/* Check CPU_STT/CPU_ERR */
	helene_read_regs(priv, 0x1A, rdata, sizeof(rdata));

	if (rdata[0] != 0x00) {
		dev_err(&priv->i2c->dev,
				"HELENE tuner CPU error 0x%x\n", rdata[0]);
		return -EIO;
	}

	/* VCO current setting */
	cdata[0] = 0x90;
	cdata[1] = 0x06;
	helene_write_regs(priv, 0x17, cdata, sizeof(cdata));
	msleep(20);
	helene_read_reg(priv, 0x19, data);
	helene_write_reg(priv, 0x95, (uint8_t)((data[0] >> 4) & 0x0F));

	/* Disable IF signal output */
	helene_write_reg(priv, 0x74, 0x02);

	/* Standby setting for CPU */
	helene_write_reg(priv, 0x88, 0x00);

	/* Standby setting for internal logic block */
	helene_write_reg(priv, 0x87, 0xC0);

	/* Load capacitance control setting for crystal oscillator */
	helene_write_reg(priv, 0x80, 0x01);

	/* Satellite initial setting */
	cdata[0] = 0x07;
	cdata[1] = 0x00;
	helene_write_regs(priv, 0x41, cdata, sizeof(cdata));

	dev_info(&priv->i2c->dev,
			"HELENE tuner x_pon done\n");

	return 0;
}