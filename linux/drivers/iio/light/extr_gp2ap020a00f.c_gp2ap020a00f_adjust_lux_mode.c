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
typedef  int u8 ;
struct gp2ap020a00f_data {TYPE_1__* client; int /*<<< orphan*/  flags; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GP2AP020A00F_ALS_REG ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_ALS_FALLING_EV ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_ALS_RISING_EV ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_LUX_MODE_HI ; 
 int /*<<< orphan*/  GP2AP020A00F_OP3_MASK ; 
 int GP2AP020A00F_OP3_OPERATION ; 
 int GP2AP020A00F_OP3_SHUTDOWN ; 
 int /*<<< orphan*/  GP2AP020A00F_OP_REG ; 
 int /*<<< orphan*/  GP2AP020A00F_RANGE_A_MASK ; 
 int GP2AP020A00F_RANGE_A_x128 ; 
 int GP2AP020A00F_RANGE_A_x8 ; 
 int /*<<< orphan*/  GP2AP020A00F_THRESH_TH ; 
 int /*<<< orphan*/  GP2AP020A00F_THRESH_TL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int gp2ap020a00f_write_event_threshold (struct gp2ap020a00f_data*,int /*<<< orphan*/ ,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool gp2ap020a00f_adjust_lux_mode(struct gp2ap020a00f_data *data,
				 int output_val)
{
	u8 new_range = 0xff;
	int err;

	if (!test_bit(GP2AP020A00F_FLAG_LUX_MODE_HI, &data->flags)) {
		if (output_val > 16000) {
			set_bit(GP2AP020A00F_FLAG_LUX_MODE_HI, &data->flags);
			new_range = GP2AP020A00F_RANGE_A_x128;
		}
	} else {
		if (output_val < 1000) {
			clear_bit(GP2AP020A00F_FLAG_LUX_MODE_HI, &data->flags);
			new_range = GP2AP020A00F_RANGE_A_x8;
		}
	}

	if (new_range != 0xff) {
		/* Clear als threshold registers to avoid spurious
		 * events caused by lux mode transition.
		 */
		err =  gp2ap020a00f_write_event_threshold(data,
					GP2AP020A00F_THRESH_TH, false);
		if (err < 0) {
			dev_err(&data->client->dev,
				"Clearing als threshold register failed.\n");
			return false;
		}

		err =  gp2ap020a00f_write_event_threshold(data,
					GP2AP020A00F_THRESH_TL, false);
		if (err < 0) {
			dev_err(&data->client->dev,
				"Clearing als threshold register failed.\n");
			return false;
		}

		/* Change lux mode */
		err = regmap_update_bits(data->regmap,
			GP2AP020A00F_OP_REG,
			GP2AP020A00F_OP3_MASK,
			GP2AP020A00F_OP3_SHUTDOWN);

		if (err < 0) {
			dev_err(&data->client->dev,
				"Shutting down the device failed.\n");
			return false;
		}

		err = regmap_update_bits(data->regmap,
			GP2AP020A00F_ALS_REG,
			GP2AP020A00F_RANGE_A_MASK,
			new_range);

		if (err < 0) {
			dev_err(&data->client->dev,
				"Adjusting device lux mode failed.\n");
			return false;
		}

		err = regmap_update_bits(data->regmap,
			GP2AP020A00F_OP_REG,
			GP2AP020A00F_OP3_MASK,
			GP2AP020A00F_OP3_OPERATION);

		if (err < 0) {
			dev_err(&data->client->dev,
				"Powering up the device failed.\n");
			return false;
		}

		/* Adjust als threshold register values to the new lux mode */
		if (test_bit(GP2AP020A00F_FLAG_ALS_RISING_EV, &data->flags)) {
			err =  gp2ap020a00f_write_event_threshold(data,
					GP2AP020A00F_THRESH_TH, true);
			if (err < 0) {
				dev_err(&data->client->dev,
				"Adjusting als threshold value failed.\n");
				return false;
			}
		}

		if (test_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV, &data->flags)) {
			err =  gp2ap020a00f_write_event_threshold(data,
					GP2AP020A00F_THRESH_TL, true);
			if (err < 0) {
				dev_err(&data->client->dev,
				"Adjusting als threshold value failed.\n");
				return false;
			}
		}

		return true;
	}

	return false;
}