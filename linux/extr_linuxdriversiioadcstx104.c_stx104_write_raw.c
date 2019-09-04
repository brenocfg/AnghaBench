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
struct stx104_iio {int* chan_out_states; int /*<<< orphan*/  base; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t channel; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_HARDWAREGAIN 129 
#define  IIO_CHAN_INFO_RAW 128 
 struct stx104_iio* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stx104_write_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int val, int val2, long mask)
{
	struct stx104_iio *const priv = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_HARDWAREGAIN:
		/* Only four gain states (x1, x2, x4, x8) */
		switch (val) {
		case 1:
			outb(0, priv->base + 11);
			break;
		case 2:
			outb(1, priv->base + 11);
			break;
		case 4:
			outb(2, priv->base + 11);
			break;
		case 8:
			outb(3, priv->base + 11);
			break;
		default:
			return -EINVAL;
		}

		return 0;
	case IIO_CHAN_INFO_RAW:
		if (chan->output) {
			/* DAC can only accept up to a 16-bit value */
			if ((unsigned int)val > 65535)
				return -EINVAL;

			priv->chan_out_states[chan->channel] = val;
			outw(val, priv->base + 4 + 2 * chan->channel);

			return 0;
		}
		return -EINVAL;
	}

	return -EINVAL;
}