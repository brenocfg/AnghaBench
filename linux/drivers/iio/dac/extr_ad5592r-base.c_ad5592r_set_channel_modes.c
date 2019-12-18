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
typedef  int u16 ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct ad5592r_state {unsigned int num_channels; int* channel_modes; int gpio_map; int gpio_in; int gpio_out; int gpio_val; int /*<<< orphan*/ * channel_offstate; struct ad5592r_rw_ops* ops; } ;
struct ad5592r_rw_ops {int (* reg_write ) (struct ad5592r_state*,int /*<<< orphan*/ ,int) ;int (* reg_read ) (struct ad5592r_state*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AD5592R_REG_ADC_EN ; 
 int /*<<< orphan*/  AD5592R_REG_DAC_EN ; 
 int /*<<< orphan*/  AD5592R_REG_GPIO_IN_EN ; 
 int /*<<< orphan*/  AD5592R_REG_GPIO_OUT_EN ; 
 int /*<<< orphan*/  AD5592R_REG_GPIO_SET ; 
 int /*<<< orphan*/  AD5592R_REG_PULLDOWN ; 
 int /*<<< orphan*/  AD5592R_REG_TRISTATE ; 
 int BIT (unsigned int) ; 
#define  CH_MODE_ADC 136 
#define  CH_MODE_DAC 135 
#define  CH_MODE_DAC_AND_ADC 134 
#define  CH_MODE_GPIO 133 
#define  CH_MODE_UNUSED 132 
#define  CH_OFFSTATE_OUT_HIGH 131 
#define  CH_OFFSTATE_OUT_LOW 130 
#define  CH_OFFSTATE_OUT_TRISTATE 129 
#define  CH_OFFSTATE_PULLDOWN 128 
 int EIO ; 
 struct iio_dev* iio_priv_to_dev (struct ad5592r_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ad5592r_state*,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct ad5592r_state*,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct ad5592r_state*,int /*<<< orphan*/ ,int) ; 
 int stub4 (struct ad5592r_state*,int /*<<< orphan*/ ,int) ; 
 int stub5 (struct ad5592r_state*,int /*<<< orphan*/ ,int) ; 
 int stub6 (struct ad5592r_state*,int /*<<< orphan*/ ,int) ; 
 int stub7 (struct ad5592r_state*,int /*<<< orphan*/ ,int) ; 
 int stub8 (struct ad5592r_state*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ad5592r_set_channel_modes(struct ad5592r_state *st)
{
	const struct ad5592r_rw_ops *ops = st->ops;
	int ret;
	unsigned i;
	struct iio_dev *iio_dev = iio_priv_to_dev(st);
	u8 pulldown = 0, tristate = 0, dac = 0, adc = 0;
	u16 read_back;

	for (i = 0; i < st->num_channels; i++) {
		switch (st->channel_modes[i]) {
		case CH_MODE_DAC:
			dac |= BIT(i);
			break;

		case CH_MODE_ADC:
			adc |= BIT(i);
			break;

		case CH_MODE_DAC_AND_ADC:
			dac |= BIT(i);
			adc |= BIT(i);
			break;

		case CH_MODE_GPIO:
			st->gpio_map |= BIT(i);
			st->gpio_in |= BIT(i); /* Default to input */
			break;

		case CH_MODE_UNUSED:
			/* fall-through */
		default:
			switch (st->channel_offstate[i]) {
			case CH_OFFSTATE_OUT_TRISTATE:
				tristate |= BIT(i);
				break;

			case CH_OFFSTATE_OUT_LOW:
				st->gpio_out |= BIT(i);
				break;

			case CH_OFFSTATE_OUT_HIGH:
				st->gpio_out |= BIT(i);
				st->gpio_val |= BIT(i);
				break;

			case CH_OFFSTATE_PULLDOWN:
				/* fall-through */
			default:
				pulldown |= BIT(i);
				break;
			}
		}
	}

	mutex_lock(&iio_dev->mlock);

	/* Pull down unused pins to GND */
	ret = ops->reg_write(st, AD5592R_REG_PULLDOWN, pulldown);
	if (ret)
		goto err_unlock;

	ret = ops->reg_write(st, AD5592R_REG_TRISTATE, tristate);
	if (ret)
		goto err_unlock;

	/* Configure pins that we use */
	ret = ops->reg_write(st, AD5592R_REG_DAC_EN, dac);
	if (ret)
		goto err_unlock;

	ret = ops->reg_write(st, AD5592R_REG_ADC_EN, adc);
	if (ret)
		goto err_unlock;

	ret = ops->reg_write(st, AD5592R_REG_GPIO_SET, st->gpio_val);
	if (ret)
		goto err_unlock;

	ret = ops->reg_write(st, AD5592R_REG_GPIO_OUT_EN, st->gpio_out);
	if (ret)
		goto err_unlock;

	ret = ops->reg_write(st, AD5592R_REG_GPIO_IN_EN, st->gpio_in);
	if (ret)
		goto err_unlock;

	/* Verify that we can read back at least one register */
	ret = ops->reg_read(st, AD5592R_REG_ADC_EN, &read_back);
	if (!ret && (read_back & 0xff) != adc)
		ret = -EIO;

err_unlock:
	mutex_unlock(&iio_dev->mlock);
	return ret;
}