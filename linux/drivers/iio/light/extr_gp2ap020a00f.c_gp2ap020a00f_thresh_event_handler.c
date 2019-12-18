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
typedef  unsigned int u8 ;
struct iio_dev {int dummy; } ;
struct gp2ap020a00f_data {scalar_t__ cur_opmode; unsigned int* thresh_val; int /*<<< orphan*/  work; int /*<<< orphan*/  flags; int /*<<< orphan*/  data_ready_queue; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  GP2AP020A00F_D0_L_REG ; 
 unsigned int GP2AP020A00F_FLAG_A ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_ALS_CLEAR_TRIGGER ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_ALS_FALLING_EV ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_ALS_IR_TRIGGER ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_ALS_RISING_EV ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_DATA_READY ; 
 unsigned int GP2AP020A00F_FLAG_P ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_PROX_TRIGGER ; 
 scalar_t__ GP2AP020A00F_OPMODE_PROX_DETECT ; 
 scalar_t__ GP2AP020A00F_OPMODE_READ_RAW_CLEAR ; 
 scalar_t__ GP2AP020A00F_OPMODE_READ_RAW_IR ; 
 scalar_t__ GP2AP020A00F_OPMODE_READ_RAW_PROXIMITY ; 
 int /*<<< orphan*/  GP2AP020A00F_OP_REG ; 
 unsigned int GP2AP020A00F_PROX_DETECT ; 
 int /*<<< orphan*/  GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR ; 
 int GP2AP020A00F_THRESH_VAL_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GP2AP020A00F_TH_L_REG ; 
 int /*<<< orphan*/  GP2AP020A00F_TL_L_REG ; 
 int /*<<< orphan*/  IIO_EV_DIR_FALLING ; 
 int /*<<< orphan*/  IIO_EV_DIR_RISING ; 
 int /*<<< orphan*/  IIO_EV_TYPE_THRESH ; 
 int /*<<< orphan*/  IIO_LIGHT ; 
 int /*<<< orphan*/  IIO_MOD_EVENT_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IIO_MOD_LIGHT_CLEAR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ gp2ap020a00f_adjust_lux_mode (struct gp2ap020a00f_data*,unsigned int) ; 
 int /*<<< orphan*/  gp2ap020a00f_output_to_lux (struct gp2ap020a00f_data*,unsigned int*) ; 
 int /*<<< orphan*/  iio_get_time_ns (struct iio_dev*) ; 
 struct gp2ap020a00f_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_push_event (struct iio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 
 unsigned int le16_to_cpup (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t gp2ap020a00f_thresh_event_handler(int irq, void *data)
{
	struct iio_dev *indio_dev = data;
	struct gp2ap020a00f_data *priv = iio_priv(indio_dev);
	u8 op_reg_flags, d0_reg_buf[2];
	unsigned int output_val, op_reg_val;
	int thresh_val_id, ret;

	/* Read interrupt flags */
	ret = regmap_read(priv->regmap, GP2AP020A00F_OP_REG,
							&op_reg_val);
	if (ret < 0)
		goto done;

	op_reg_flags = op_reg_val & (GP2AP020A00F_FLAG_A | GP2AP020A00F_FLAG_P
					| GP2AP020A00F_PROX_DETECT);

	op_reg_val &= (~GP2AP020A00F_FLAG_A & ~GP2AP020A00F_FLAG_P
					& ~GP2AP020A00F_PROX_DETECT);

	/* Clear interrupt flags (if not in INTTYPE_PULSE mode) */
	if (priv->cur_opmode != GP2AP020A00F_OPMODE_PROX_DETECT) {
		ret = regmap_write(priv->regmap, GP2AP020A00F_OP_REG,
								op_reg_val);
		if (ret < 0)
			goto done;
	}

	if (op_reg_flags & GP2AP020A00F_FLAG_A) {
		/* Check D0 register to assess if the lux mode
		 * transition is required.
		 */
		ret = regmap_bulk_read(priv->regmap, GP2AP020A00F_D0_L_REG,
							d0_reg_buf, 2);
		if (ret < 0)
			goto done;

		output_val = le16_to_cpup((__le16 *)d0_reg_buf);

		if (gp2ap020a00f_adjust_lux_mode(priv, output_val))
			goto done;

		gp2ap020a00f_output_to_lux(priv, &output_val);

		/*
		 * We need to check output value to distinguish
		 * between high and low ambient light threshold event.
		 */
		if (test_bit(GP2AP020A00F_FLAG_ALS_RISING_EV, &priv->flags)) {
			thresh_val_id =
			    GP2AP020A00F_THRESH_VAL_ID(GP2AP020A00F_TH_L_REG);
			if (output_val > priv->thresh_val[thresh_val_id])
				iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(
					    IIO_LIGHT,
					    GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR,
					    IIO_MOD_LIGHT_CLEAR,
					    IIO_EV_TYPE_THRESH,
					    IIO_EV_DIR_RISING),
				       iio_get_time_ns(indio_dev));
		}

		if (test_bit(GP2AP020A00F_FLAG_ALS_FALLING_EV, &priv->flags)) {
			thresh_val_id =
			    GP2AP020A00F_THRESH_VAL_ID(GP2AP020A00F_TL_L_REG);
			if (output_val < priv->thresh_val[thresh_val_id])
				iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(
					    IIO_LIGHT,
					    GP2AP020A00F_SCAN_MODE_LIGHT_CLEAR,
					    IIO_MOD_LIGHT_CLEAR,
					    IIO_EV_TYPE_THRESH,
					    IIO_EV_DIR_FALLING),
				       iio_get_time_ns(indio_dev));
		}
	}

	if (priv->cur_opmode == GP2AP020A00F_OPMODE_READ_RAW_CLEAR ||
	    priv->cur_opmode == GP2AP020A00F_OPMODE_READ_RAW_IR ||
	    priv->cur_opmode == GP2AP020A00F_OPMODE_READ_RAW_PROXIMITY) {
		set_bit(GP2AP020A00F_FLAG_DATA_READY, &priv->flags);
		wake_up(&priv->data_ready_queue);
		goto done;
	}

	if (test_bit(GP2AP020A00F_FLAG_ALS_CLEAR_TRIGGER, &priv->flags) ||
	    test_bit(GP2AP020A00F_FLAG_ALS_IR_TRIGGER, &priv->flags) ||
	    test_bit(GP2AP020A00F_FLAG_PROX_TRIGGER, &priv->flags))
		/* This fires off the trigger. */
		irq_work_queue(&priv->work);

done:
	return IRQ_HANDLED;
}