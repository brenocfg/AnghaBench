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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; } ;
struct cio_dac_iio {int* chan_out_states; scalar_t__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 long IIO_CHAN_INFO_RAW ; 
 struct cio_dac_iio* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static int cio_dac_write_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int val, int val2, long mask)
{
	struct cio_dac_iio *const priv = iio_priv(indio_dev);
	const unsigned int chan_addr_offset = 2 * chan->channel;

	if (mask != IIO_CHAN_INFO_RAW)
		return -EINVAL;

	/* DAC can only accept up to a 16-bit value */
	if ((unsigned int)val > 65535)
		return -EINVAL;

	priv->chan_out_states[chan->channel] = val;
	outw(val, priv->base + chan_addr_offset);

	return 0;
}