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
struct quad8_iio {int base; int* preset; int* ab_enable; int* preset_enable; int* quadrature_scale; int /*<<< orphan*/ * quadrature_mode; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_ENABLE 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int /*<<< orphan*/  IIO_INDEX ; 
 unsigned int QUAD8_CTR_IOR ; 
 unsigned int QUAD8_CTR_RLD ; 
 unsigned int QUAD8_RLD_PRESET_CNTR ; 
 unsigned int QUAD8_RLD_RESET_BP ; 
 unsigned int QUAD8_RLD_RESET_E ; 
 unsigned int QUAD8_RLD_RESET_FLAGS ; 
 struct quad8_iio* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  outb (unsigned int,int const) ; 

__attribute__((used)) static int quad8_write_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int val, int val2, long mask)
{
	struct quad8_iio *const priv = iio_priv(indio_dev);
	const int base_offset = priv->base + 2 * chan->channel;
	int i;
	unsigned int ior_cfg;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (chan->type == IIO_INDEX)
			return -EINVAL;

		/* Only 24-bit values are supported */
		if ((unsigned int)val > 0xFFFFFF)
			return -EINVAL;

		/* Reset Byte Pointer */
		outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP, base_offset + 1);

		/* Counter can only be set via Preset Register */
		for (i = 0; i < 3; i++)
			outb(val >> (8 * i), base_offset);

		/* Transfer Preset Register to Counter */
		outb(QUAD8_CTR_RLD | QUAD8_RLD_PRESET_CNTR, base_offset + 1);

		/* Reset Byte Pointer */
		outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP, base_offset + 1);

		/* Set Preset Register back to original value */
		val = priv->preset[chan->channel];
		for (i = 0; i < 3; i++)
			outb(val >> (8 * i), base_offset);

		/* Reset Borrow, Carry, Compare, and Sign flags */
		outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_FLAGS, base_offset + 1);
		/* Reset Error flag */
		outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_E, base_offset + 1);

		return 0;
	case IIO_CHAN_INFO_ENABLE:
		/* only boolean values accepted */
		if (val < 0 || val > 1)
			return -EINVAL;

		priv->ab_enable[chan->channel] = val;

		ior_cfg = val | priv->preset_enable[chan->channel] << 1;

		/* Load I/O control configuration */
		outb(QUAD8_CTR_IOR | ior_cfg, base_offset + 1);

		return 0;
	case IIO_CHAN_INFO_SCALE:
		/* Quadrature scaling only available in quadrature mode */
		if (!priv->quadrature_mode[chan->channel] && (val2 || val != 1))
			return -EINVAL;

		/* Only three gain states (1, 0.5, 0.25) */
		if (val == 1 && !val2)
			priv->quadrature_scale[chan->channel] = 0;
		else if (!val)
			switch (val2) {
			case 500000:
				priv->quadrature_scale[chan->channel] = 1;
				break;
			case 250000:
				priv->quadrature_scale[chan->channel] = 2;
				break;
			default:
				return -EINVAL;
			}
		else
			return -EINVAL;

		return 0;
	}

	return -EINVAL;
}