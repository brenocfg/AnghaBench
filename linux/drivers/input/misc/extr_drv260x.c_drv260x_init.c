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
struct drv260x_data {unsigned int rated_voltage; unsigned int overdrive_voltage; int mode; TYPE_1__* client; int /*<<< orphan*/  regmap; int /*<<< orphan*/  library; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  DRV260X_ERM_MODE 129 
 int /*<<< orphan*/  DRV260X_GO ; 
 unsigned int DRV260X_GO_BIT ; 
 int /*<<< orphan*/  DRV260X_LIB_SEL ; 
 int /*<<< orphan*/  DRV260X_LIB_SEL_MASK ; 
#define  DRV260X_LRA_MODE 128 
 int /*<<< orphan*/  DRV260X_OD_CLAMP_VOLT ; 
 int /*<<< orphan*/  DRV260X_RATED_VOLT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  drv260x_erm_cal_regs ; 
 int /*<<< orphan*/  drv260x_lra_cal_regs ; 
 int /*<<< orphan*/  drv260x_lra_init_regs ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_register_patch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int drv260x_init(struct drv260x_data *haptics)
{
	int error;
	unsigned int cal_buf;

	error = regmap_write(haptics->regmap,
			     DRV260X_RATED_VOLT, haptics->rated_voltage);
	if (error) {
		dev_err(&haptics->client->dev,
			"Failed to write DRV260X_RATED_VOLT register: %d\n",
			error);
		return error;
	}

	error = regmap_write(haptics->regmap,
			     DRV260X_OD_CLAMP_VOLT, haptics->overdrive_voltage);
	if (error) {
		dev_err(&haptics->client->dev,
			"Failed to write DRV260X_OD_CLAMP_VOLT register: %d\n",
			error);
		return error;
	}

	switch (haptics->mode) {
	case DRV260X_LRA_MODE:
		error = regmap_register_patch(haptics->regmap,
					      drv260x_lra_cal_regs,
					      ARRAY_SIZE(drv260x_lra_cal_regs));
		if (error) {
			dev_err(&haptics->client->dev,
				"Failed to write LRA calibration registers: %d\n",
				error);
			return error;
		}

		break;

	case DRV260X_ERM_MODE:
		error = regmap_register_patch(haptics->regmap,
					      drv260x_erm_cal_regs,
					      ARRAY_SIZE(drv260x_erm_cal_regs));
		if (error) {
			dev_err(&haptics->client->dev,
				"Failed to write ERM calibration registers: %d\n",
				error);
			return error;
		}

		error = regmap_update_bits(haptics->regmap, DRV260X_LIB_SEL,
					   DRV260X_LIB_SEL_MASK,
					   haptics->library);
		if (error) {
			dev_err(&haptics->client->dev,
				"Failed to write DRV260X_LIB_SEL register: %d\n",
				error);
			return error;
		}

		break;

	default:
		error = regmap_register_patch(haptics->regmap,
					      drv260x_lra_init_regs,
					      ARRAY_SIZE(drv260x_lra_init_regs));
		if (error) {
			dev_err(&haptics->client->dev,
				"Failed to write LRA init registers: %d\n",
				error);
			return error;
		}

		error = regmap_update_bits(haptics->regmap, DRV260X_LIB_SEL,
					   DRV260X_LIB_SEL_MASK,
					   haptics->library);
		if (error) {
			dev_err(&haptics->client->dev,
				"Failed to write DRV260X_LIB_SEL register: %d\n",
				error);
			return error;
		}

		/* No need to set GO bit here */
		return 0;
	}

	error = regmap_write(haptics->regmap, DRV260X_GO, DRV260X_GO_BIT);
	if (error) {
		dev_err(&haptics->client->dev,
			"Failed to write GO register: %d\n",
			error);
		return error;
	}

	do {
		error = regmap_read(haptics->regmap, DRV260X_GO, &cal_buf);
		if (error) {
			dev_err(&haptics->client->dev,
				"Failed to read GO register: %d\n",
				error);
			return error;
		}
	} while (cal_buf == DRV260X_GO_BIT);

	return 0;
}