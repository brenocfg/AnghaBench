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
struct quad8_iio {int base; unsigned int* preset; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int channel; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int QUAD8_CTR_RLD ; 
 unsigned int QUAD8_RLD_RESET_BP ; 
 struct quad8_iio* iio_priv (struct iio_dev*) ; 
 int kstrtouint (char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  outb (unsigned int,int const) ; 

__attribute__((used)) static ssize_t quad8_write_preset(struct iio_dev *indio_dev, uintptr_t private,
	const struct iio_chan_spec *chan, const char *buf, size_t len)
{
	struct quad8_iio *const priv = iio_priv(indio_dev);
	const int base_offset = priv->base + 2 * chan->channel;
	unsigned int preset;
	int ret;
	int i;

	ret = kstrtouint(buf, 0, &preset);
	if (ret)
		return ret;

	/* Only 24-bit values are supported */
	if (preset > 0xFFFFFF)
		return -EINVAL;

	priv->preset[chan->channel] = preset;

	/* Reset Byte Pointer */
	outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP, base_offset + 1);

	/* Set Preset Register */
	for (i = 0; i < 3; i++)
		outb(preset >> (8 * i), base_offset);

	return len;
}