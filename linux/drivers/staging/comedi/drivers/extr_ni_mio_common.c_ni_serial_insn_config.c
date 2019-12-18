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
struct ni_private {unsigned int clock_and_fout; int serial_hw_mode; int dio_control; unsigned int serial_interval_ns; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct ni_private* private; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INSN_CONFIG_BIDIRECTIONAL_DATA 129 
#define  INSN_CONFIG_SERIAL_CLOCK 128 
 unsigned int NISTC_CLK_FOUT_DIO_SER_OUT_DIV2 ; 
 int /*<<< orphan*/  NISTC_CLK_FOUT_REG ; 
 unsigned int NISTC_CLK_FOUT_SLOW_TIMEBASE ; 
 int NISTC_DIO_CTRL_HW_SER_ENA ; 
 int NISTC_DIO_CTRL_HW_SER_TIMEBASE ; 
 int /*<<< orphan*/  NISTC_DIO_CTRL_REG ; 
 int NISTC_DIO_SDCLK ; 
 unsigned int SERIAL_10US ; 
 unsigned int SERIAL_1_2US ; 
 unsigned int SERIAL_600NS ; 
 unsigned int SERIAL_DISABLED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ni_serial_hw_readwrite8 (struct comedi_device*,struct comedi_subdevice*,unsigned char,unsigned char*) ; 
 int ni_serial_sw_readwrite8 (struct comedi_device*,struct comedi_subdevice*,unsigned char,unsigned char*) ; 
 int /*<<< orphan*/  ni_stc_writew (struct comedi_device*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_serial_insn_config(struct comedi_device *dev,
				 struct comedi_subdevice *s,
				 struct comedi_insn *insn,
				 unsigned int *data)
{
	struct ni_private *devpriv = dev->private;
	unsigned int clk_fout = devpriv->clock_and_fout;
	int err = insn->n;
	unsigned char byte_out, byte_in = 0;

	if (insn->n != 2)
		return -EINVAL;

	switch (data[0]) {
	case INSN_CONFIG_SERIAL_CLOCK:
		devpriv->serial_hw_mode = 1;
		devpriv->dio_control |= NISTC_DIO_CTRL_HW_SER_ENA;

		if (data[1] == SERIAL_DISABLED) {
			devpriv->serial_hw_mode = 0;
			devpriv->dio_control &= ~(NISTC_DIO_CTRL_HW_SER_ENA |
						  NISTC_DIO_SDCLK);
			data[1] = SERIAL_DISABLED;
			devpriv->serial_interval_ns = data[1];
		} else if (data[1] <= SERIAL_600NS) {
			/*
			 * Warning: this clock speed is too fast to reliably
			 * control SCXI.
			 */
			devpriv->dio_control &= ~NISTC_DIO_CTRL_HW_SER_TIMEBASE;
			clk_fout |= NISTC_CLK_FOUT_SLOW_TIMEBASE;
			clk_fout &= ~NISTC_CLK_FOUT_DIO_SER_OUT_DIV2;
			data[1] = SERIAL_600NS;
			devpriv->serial_interval_ns = data[1];
		} else if (data[1] <= SERIAL_1_2US) {
			devpriv->dio_control &= ~NISTC_DIO_CTRL_HW_SER_TIMEBASE;
			clk_fout |= NISTC_CLK_FOUT_SLOW_TIMEBASE |
				    NISTC_CLK_FOUT_DIO_SER_OUT_DIV2;
			data[1] = SERIAL_1_2US;
			devpriv->serial_interval_ns = data[1];
		} else if (data[1] <= SERIAL_10US) {
			devpriv->dio_control |= NISTC_DIO_CTRL_HW_SER_TIMEBASE;
			clk_fout |= NISTC_CLK_FOUT_SLOW_TIMEBASE |
				    NISTC_CLK_FOUT_DIO_SER_OUT_DIV2;
			/*
			 * Note: NISTC_CLK_FOUT_DIO_SER_OUT_DIV2 only affects
			 * 600ns/1.2us. If you turn divide_by_2 off with the
			 * slow clock, you will still get 10us, except then
			 * all your delays are wrong.
			 */
			data[1] = SERIAL_10US;
			devpriv->serial_interval_ns = data[1];
		} else {
			devpriv->dio_control &= ~(NISTC_DIO_CTRL_HW_SER_ENA |
						  NISTC_DIO_SDCLK);
			devpriv->serial_hw_mode = 0;
			data[1] = (data[1] / 1000) * 1000;
			devpriv->serial_interval_ns = data[1];
		}
		devpriv->clock_and_fout = clk_fout;

		ni_stc_writew(dev, devpriv->dio_control, NISTC_DIO_CTRL_REG);
		ni_stc_writew(dev, devpriv->clock_and_fout, NISTC_CLK_FOUT_REG);
		return 1;

	case INSN_CONFIG_BIDIRECTIONAL_DATA:

		if (devpriv->serial_interval_ns == 0)
			return -EINVAL;

		byte_out = data[1] & 0xFF;

		if (devpriv->serial_hw_mode) {
			err = ni_serial_hw_readwrite8(dev, s, byte_out,
						      &byte_in);
		} else if (devpriv->serial_interval_ns > 0) {
			err = ni_serial_sw_readwrite8(dev, s, byte_out,
						      &byte_in);
		} else {
			dev_err(dev->class_dev, "serial disabled!\n");
			return -EINVAL;
		}
		if (err < 0)
			return err;
		data[1] = byte_in & 0xFF;
		return insn->n;

		break;
	default:
		return -EINVAL;
	}
}