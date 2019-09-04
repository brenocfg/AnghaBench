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
typedef  scalar_t__ u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct bh1770_chip {int prox_coef; int prox_const; int /*<<< orphan*/  chipname; int /*<<< orphan*/  lux_cf; scalar_t__ revision; struct i2c_client* client; } ;
typedef  int s32 ;

/* Variables and functions */
 int BH1770_COEF_SCALER ; 
 int /*<<< orphan*/  BH1770_MANUFACT_ID ; 
 scalar_t__ BH1770_MANUFACT_OSRAM ; 
 scalar_t__ BH1770_MANUFACT_ROHM ; 
 int /*<<< orphan*/  BH1770_NEUTRAL_CF ; 
 scalar_t__ BH1770_PART ; 
 int /*<<< orphan*/  BH1770_PART_ID ; 
 scalar_t__ BH1770_PART_MASK ; 
 scalar_t__ BH1770_REV_MASK ; 
 scalar_t__ BH1770_REV_SHIFT ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int bh1770_detect(struct bh1770_chip *chip)
{
	struct i2c_client *client = chip->client;
	s32 ret;
	u8 manu, part;

	ret = i2c_smbus_read_byte_data(client, BH1770_MANUFACT_ID);
	if (ret < 0)
		goto error;
	manu = (u8)ret;

	ret = i2c_smbus_read_byte_data(client, BH1770_PART_ID);
	if (ret < 0)
		goto error;
	part = (u8)ret;

	chip->revision = (part & BH1770_REV_MASK) >> BH1770_REV_SHIFT;
	chip->prox_coef = BH1770_COEF_SCALER;
	chip->prox_const = 0;
	chip->lux_cf = BH1770_NEUTRAL_CF;

	if ((manu == BH1770_MANUFACT_ROHM) &&
	    ((part & BH1770_PART_MASK) == BH1770_PART)) {
		snprintf(chip->chipname, sizeof(chip->chipname), "BH1770GLC");
		return 0;
	}

	if ((manu == BH1770_MANUFACT_OSRAM) &&
	    ((part & BH1770_PART_MASK) == BH1770_PART)) {
		snprintf(chip->chipname, sizeof(chip->chipname), "SFH7770");
		/* Values selected by comparing different versions */
		chip->prox_coef = 819; /* 0.8 * BH1770_COEF_SCALER */
		chip->prox_const = 40;
		return 0;
	}

	ret = -ENODEV;
error:
	dev_dbg(&client->dev, "BH1770 or SFH7770 not found\n");

	return ret;
}