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
typedef  size_t u8 ;
struct mcp3422 {int /*<<< orphan*/  config; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 size_t MCP3422_PGA (int /*<<< orphan*/ ) ; 
 size_t MCP3422_SAMPLE_RATE (int /*<<< orphan*/ ) ; 
 struct mcp3422* iio_priv (struct iio_dev*) ; 
 int mcp3422_read_channel (struct mcp3422*,struct iio_chan_spec const*,int*) ; 
 int* mcp3422_sample_rates ; 
 int** mcp3422_scales ; 

__attribute__((used)) static int mcp3422_read_raw(struct iio_dev *iio,
			struct iio_chan_spec const *channel, int *val1,
			int *val2, long mask)
{
	struct mcp3422 *adc = iio_priv(iio);
	int err;

	u8 sample_rate = MCP3422_SAMPLE_RATE(adc->config);
	u8 pga		 = MCP3422_PGA(adc->config);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		err = mcp3422_read_channel(adc, channel, val1);
		if (err < 0)
			return -EINVAL;
		return IIO_VAL_INT;

	case IIO_CHAN_INFO_SCALE:

		*val1 = 0;
		*val2 = mcp3422_scales[sample_rate][pga];
		return IIO_VAL_INT_PLUS_NANO;

	case IIO_CHAN_INFO_SAMP_FREQ:
		*val1 = mcp3422_sample_rates[MCP3422_SAMPLE_RATE(adc->config)];
		return IIO_VAL_INT;

	default:
		break;
	}

	return -EINVAL;
}