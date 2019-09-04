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
typedef  int u8 ;
struct sd {int dummy; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBI ; 
 int /*<<< orphan*/  R511_I2C_CTL ; 
 int /*<<< orphan*/  R51x_I2C_DATA ; 
 int /*<<< orphan*/  R51x_I2C_SADDR_2 ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,...) ; 
 int reg_r (struct sd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov511_i2c_r(struct sd *sd, u8 reg)
{
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;
	int rc, value, retries;

	/* Two byte write cycle */
	for (retries = 6; ; ) {
		/* Select camera register */
		reg_w(sd, R51x_I2C_SADDR_2, reg);

		/* Initiate 2-byte write cycle */
		reg_w(sd, R511_I2C_CTL, 0x03);

		do {
			rc = reg_r(sd, R511_I2C_CTL);
		} while (rc > 0 && ((rc & 1) == 0)); /* Retry until idle */

		if (rc < 0)
			return rc;

		if ((rc & 2) == 0) /* Ack? */
			break;

		/* I2C abort */
		reg_w(sd, R511_I2C_CTL, 0x10);

		if (--retries < 0) {
			gspca_dbg(gspca_dev, D_USBI, "i2c write retries exhausted\n");
			return -1;
		}
	}

	/* Two byte read cycle */
	for (retries = 6; ; ) {
		/* Initiate 2-byte read cycle */
		reg_w(sd, R511_I2C_CTL, 0x05);

		do {
			rc = reg_r(sd, R511_I2C_CTL);
		} while (rc > 0 && ((rc & 1) == 0)); /* Retry until idle */

		if (rc < 0)
			return rc;

		if ((rc & 2) == 0) /* Ack? */
			break;

		/* I2C abort */
		reg_w(sd, R511_I2C_CTL, 0x10);

		if (--retries < 0) {
			gspca_dbg(gspca_dev, D_USBI, "i2c read retries exhausted\n");
			return -1;
		}
	}

	value = reg_r(sd, R51x_I2C_DATA);

	gspca_dbg(gspca_dev, D_USBI, "ov511_i2c_r %02x %02x\n", reg, value);

	/* This is needed to make i2c_w() work */
	reg_w(sd, R511_I2C_CTL, 0x05);

	return value;
}