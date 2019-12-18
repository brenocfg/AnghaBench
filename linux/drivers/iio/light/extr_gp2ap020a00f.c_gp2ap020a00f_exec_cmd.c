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
struct gp2ap020a00f_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  cur_opmode; } ;
typedef  enum gp2ap020a00f_cmd { ____Placeholder_gp2ap020a00f_cmd } gp2ap020a00f_cmd ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  GP2AP020A00F_ADD_MODE ; 
#define  GP2AP020A00F_CMD_ALS_HIGH_EV_DIS 144 
#define  GP2AP020A00F_CMD_ALS_HIGH_EV_EN 143 
#define  GP2AP020A00F_CMD_ALS_LOW_EV_DIS 142 
#define  GP2AP020A00F_CMD_ALS_LOW_EV_EN 141 
#define  GP2AP020A00F_CMD_PROX_HIGH_EV_DIS 140 
#define  GP2AP020A00F_CMD_PROX_HIGH_EV_EN 139 
#define  GP2AP020A00F_CMD_PROX_LOW_EV_DIS 138 
#define  GP2AP020A00F_CMD_PROX_LOW_EV_EN 137 
#define  GP2AP020A00F_CMD_READ_RAW_CLEAR 136 
#define  GP2AP020A00F_CMD_READ_RAW_IR 135 
#define  GP2AP020A00F_CMD_READ_RAW_PROXIMITY 134 
#define  GP2AP020A00F_CMD_TRIGGER_CLEAR_DIS 133 
#define  GP2AP020A00F_CMD_TRIGGER_CLEAR_EN 132 
#define  GP2AP020A00F_CMD_TRIGGER_IR_DIS 131 
#define  GP2AP020A00F_CMD_TRIGGER_IR_EN 130 
#define  GP2AP020A00F_CMD_TRIGGER_PROX_DIS 129 
#define  GP2AP020A00F_CMD_TRIGGER_PROX_EN 128 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_ALS_CLEAR_TRIGGER ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_ALS_FALLING_EV ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_ALS_IR_TRIGGER ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_ALS_RISING_EV ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_PROX_FALLING_EV ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_PROX_RISING_EV ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_PROX_TRIGGER ; 
 int /*<<< orphan*/  GP2AP020A00F_OPMODE_ALS ; 
 int /*<<< orphan*/  GP2AP020A00F_OPMODE_PROX_DETECT ; 
 int /*<<< orphan*/  GP2AP020A00F_OPMODE_PS ; 
 int /*<<< orphan*/  GP2AP020A00F_OPMODE_READ_RAW_CLEAR ; 
 int /*<<< orphan*/  GP2AP020A00F_OPMODE_READ_RAW_IR ; 
 int /*<<< orphan*/  GP2AP020A00F_OPMODE_READ_RAW_PROXIMITY ; 
 int /*<<< orphan*/  GP2AP020A00F_OPMODE_SHUTDOWN ; 
 int /*<<< orphan*/  GP2AP020A00F_SUBTRACT_MODE ; 
 int /*<<< orphan*/  GP2AP020A00F_THRESH_PH ; 
 int /*<<< orphan*/  GP2AP020A00F_THRESH_PL ; 
 int /*<<< orphan*/  GP2AP020A00F_THRESH_TH ; 
 int /*<<< orphan*/  GP2AP020A00F_THRESH_TL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gp2ap020a00f_als_enabled (struct gp2ap020a00f_data*) ; 
 int gp2ap020a00f_alter_opmode (struct gp2ap020a00f_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gp2ap020a00f_prox_detect_enabled (struct gp2ap020a00f_data*) ; 
 int gp2ap020a00f_set_operation_mode (struct gp2ap020a00f_data*,int /*<<< orphan*/ ) ; 
 int gp2ap020a00f_write_event_threshold (struct gp2ap020a00f_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gp2ap020a00f_exec_cmd(struct gp2ap020a00f_data *data,
					enum gp2ap020a00f_cmd cmd)
{
	int err = 0;

	switch (cmd) {
	case GP2AP020A00F_CMD_READ_RAW_CLEAR:
		if (data->cur_opmode != GP2AP020A00F_OPMODE_SHUTDOWN)
			return -EBUSY;
		err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_READ_RAW_CLEAR);
		break;
	case GP2AP020A00F_CMD_READ_RAW_IR:
		if (data->cur_opmode != GP2AP020A00F_OPMODE_SHUTDOWN)
			return -EBUSY;
		err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_READ_RAW_IR);
		break;
	case GP2AP020A00F_CMD_READ_RAW_PROXIMITY:
		if (data->cur_opmode != GP2AP020A00F_OPMODE_SHUTDOWN)
			return -EBUSY;
		err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_READ_RAW_PROXIMITY);
		break;
	case GP2AP020A00F_CMD_TRIGGER_CLEAR_EN:
		if (data->cur_opmode == GP2AP020A00F_OPMODE_PROX_DETECT)
			return -EBUSY;
		if (!gp2ap020a00f_als_enabled(data))
			err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_ADD_MODE);
		set_bit(GP2AP020A00F_FLAG_ALS_CLEAR_TRIGGER, &data->flags);
		break;
	case GP2AP020A00F_CMD_TRIGGER_CLEAR_DIS:
		clear_bit(GP2AP020A00F_FLAG_ALS_CLEAR_TRIGGER, &data->flags);
		if (gp2ap020a00f_als_enabled(data))
			break;
		err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_SUBTRACT_MODE);
		break;
	case GP2AP020A00F_CMD_TRIGGER_IR_EN:
		if (data->cur_opmode == GP2AP020A00F_OPMODE_PROX_DETECT)
			return -EBUSY;
		if (!gp2ap020a00f_als_enabled(data))
			err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_ADD_MODE);
		set_bit(GP2AP020A00F_FLAG_ALS_IR_TRIGGER, &data->flags);
		break;
	case GP2AP020A00F_CMD_TRIGGER_IR_DIS:
		clear_bit(GP2AP020A00F_FLAG_ALS_IR_TRIGGER, &data->flags);
		if (gp2ap020a00f_als_enabled(data))
			break;
		err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_SUBTRACT_MODE);
		break;
	case GP2AP020A00F_CMD_TRIGGER_PROX_EN:
		if (data->cur_opmode == GP2AP020A00F_OPMODE_PROX_DETECT)
			return -EBUSY;
		err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_PS,
						GP2AP020A00F_ADD_MODE);
		set_bit(GP2AP020A00F_FLAG_PROX_TRIGGER, &data->flags);
		break;
	case GP2AP020A00F_CMD_TRIGGER_PROX_DIS:
		clear_bit(GP2AP020A00F_FLAG_PROX_TRIGGER, &data->flags);
		err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_PS,
						GP2AP020A00F_SUBTRACT_MODE);
		break;
	case GP2AP020A00F_CMD_ALS_HIGH_EV_EN:
		if (test_bit(GP2AP020A00F_FLAG_ALS_RISING_EV, &data->flags))
			return 0;
		if (data->cur_opmode == GP2AP020A00F_OPMODE_PROX_DETECT)
			return -EBUSY;
		if (!gp2ap020a00f_als_enabled(data)) {
			err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_ADD_MODE);
			if (err < 0)
				return err;
		}
		set_bit(GP2AP020A00F_FLAG_ALS_RISING_EV, &data->flags);
		err =  gp2ap020a00f_write_event_threshold(data,
					GP2AP020A00F_THRESH_TH, true);
		break;
	case GP2AP020A00F_CMD_ALS_HIGH_EV_DIS:
		if (!test_bit(GP2AP020A00F_FLAG_ALS_RISING_EV, &data->flags))
			return 0;
		clear_bit(GP2AP020A00F_FLAG_ALS_RISING_EV, &data->flags);
		if (!gp2ap020a00f_als_enabled(data)) {
			err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_SUBTRACT_MODE);
			if (err < 0)
				return err;
		}
		err =  gp2ap020a00f_write_event_threshold(data,
					GP2AP020A00F_THRESH_TH, false);
		break;
	case GP2AP020A00F_CMD_ALS_LOW_EV_EN:
		if (test_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV, &data->flags))
			return 0;
		if (data->cur_opmode == GP2AP020A00F_OPMODE_PROX_DETECT)
			return -EBUSY;
		if (!gp2ap020a00f_als_enabled(data)) {
			err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_ADD_MODE);
			if (err < 0)
				return err;
		}
		set_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV, &data->flags);
		err =  gp2ap020a00f_write_event_threshold(data,
					GP2AP020A00F_THRESH_TL, true);
		break;
	case GP2AP020A00F_CMD_ALS_LOW_EV_DIS:
		if (!test_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV, &data->flags))
			return 0;
		clear_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV, &data->flags);
		if (!gp2ap020a00f_als_enabled(data)) {
			err = gp2ap020a00f_alter_opmode(data,
						GP2AP020A00F_OPMODE_ALS,
						GP2AP020A00F_SUBTRACT_MODE);
			if (err < 0)
				return err;
		}
		err =  gp2ap020a00f_write_event_threshold(data,
					GP2AP020A00F_THRESH_TL, false);
		break;
	case GP2AP020A00F_CMD_PROX_HIGH_EV_EN:
		if (test_bit(GP2AP020A00F_FLAG_PROX_RISING_EV, &data->flags))
			return 0;
		if (gp2ap020a00f_als_enabled(data) ||
		    data->cur_opmode == GP2AP020A00F_OPMODE_PS)
			return -EBUSY;
		if (!gp2ap020a00f_prox_detect_enabled(data)) {
			err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_PROX_DETECT);
			if (err < 0)
				return err;
		}
		set_bit(GP2AP020A00F_FLAG_PROX_RISING_EV, &data->flags);
		err =  gp2ap020a00f_write_event_threshold(data,
					GP2AP020A00F_THRESH_PH, true);
		break;
	case GP2AP020A00F_CMD_PROX_HIGH_EV_DIS:
		if (!test_bit(GP2AP020A00F_FLAG_PROX_RISING_EV, &data->flags))
			return 0;
		clear_bit(GP2AP020A00F_FLAG_PROX_RISING_EV, &data->flags);
		err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_SHUTDOWN);
		if (err < 0)
			return err;
		err =  gp2ap020a00f_write_event_threshold(data,
					GP2AP020A00F_THRESH_PH, false);
		break;
	case GP2AP020A00F_CMD_PROX_LOW_EV_EN:
		if (test_bit(GP2AP020A00F_FLAG_PROX_FALLING_EV, &data->flags))
			return 0;
		if (gp2ap020a00f_als_enabled(data) ||
		    data->cur_opmode == GP2AP020A00F_OPMODE_PS)
			return -EBUSY;
		if (!gp2ap020a00f_prox_detect_enabled(data)) {
			err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_PROX_DETECT);
			if (err < 0)
				return err;
		}
		set_bit(GP2AP020A00F_FLAG_PROX_FALLING_EV, &data->flags);
		err =  gp2ap020a00f_write_event_threshold(data,
					GP2AP020A00F_THRESH_PL, true);
		break;
	case GP2AP020A00F_CMD_PROX_LOW_EV_DIS:
		if (!test_bit(GP2AP020A00F_FLAG_PROX_FALLING_EV, &data->flags))
			return 0;
		clear_bit(GP2AP020A00F_FLAG_PROX_FALLING_EV, &data->flags);
		err = gp2ap020a00f_set_operation_mode(data,
					GP2AP020A00F_OPMODE_SHUTDOWN);
		if (err < 0)
			return err;
		err =  gp2ap020a00f_write_event_threshold(data,
					GP2AP020A00F_THRESH_PL, false);
		break;
	}

	return err;
}