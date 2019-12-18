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
struct mcp3422 {size_t config; size_t* pga; int id; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {size_t channel; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_CHAN_INFO_SCALE 128 
 size_t MCP3422_CHANNEL_MASK ; 
 size_t MCP3422_CHANNEL_VALUE (size_t) ; 
 size_t MCP3422_PGA_MASK ; 
 size_t MCP3422_PGA_VALUE (size_t) ; 
 size_t MCP3422_SAMPLE_RATE (size_t) ; 
 size_t MCP3422_SAMPLE_RATE_VALUE (size_t) ; 
 size_t MCP3422_SRATE_15 ; 
 size_t MCP3422_SRATE_240 ; 
 size_t MCP3422_SRATE_3 ; 
 size_t MCP3422_SRATE_60 ; 
 size_t MCP3422_SRATE_MASK ; 
 struct mcp3422* iio_priv (struct iio_dev*) ; 
 int** mcp3422_scales ; 
 int mcp3422_update_config (struct mcp3422*,size_t) ; 

__attribute__((used)) static int mcp3422_write_raw(struct iio_dev *iio,
			struct iio_chan_spec const *channel, int val1,
			int val2, long mask)
{
	struct mcp3422 *adc = iio_priv(iio);
	u8 temp;
	u8 config = adc->config;
	u8 req_channel = channel->channel;
	u8 sample_rate = MCP3422_SAMPLE_RATE(config);
	u8 i;

	switch (mask) {
	case IIO_CHAN_INFO_SCALE:
		if (val1 != 0)
			return -EINVAL;

		for (i = 0; i < ARRAY_SIZE(mcp3422_scales[0]); i++) {
			if (val2 == mcp3422_scales[sample_rate][i]) {
				adc->pga[req_channel] = i;

				config &= ~MCP3422_CHANNEL_MASK;
				config |= MCP3422_CHANNEL_VALUE(req_channel);
				config &= ~MCP3422_PGA_MASK;
				config |= MCP3422_PGA_VALUE(adc->pga[req_channel]);

				return mcp3422_update_config(adc, config);
			}
		}
		return -EINVAL;

	case IIO_CHAN_INFO_SAMP_FREQ:
		switch (val1) {
		case 240:
			temp = MCP3422_SRATE_240;
			break;
		case 60:
			temp = MCP3422_SRATE_60;
			break;
		case 15:
			temp = MCP3422_SRATE_15;
			break;
		case 3:
			if (adc->id > 4)
				return -EINVAL;
			temp = MCP3422_SRATE_3;
			break;
		default:
			return -EINVAL;
		}

		config &= ~MCP3422_CHANNEL_MASK;
		config |= MCP3422_CHANNEL_VALUE(req_channel);
		config &= ~MCP3422_SRATE_MASK;
		config |= MCP3422_SAMPLE_RATE_VALUE(temp);

		return mcp3422_update_config(adc, config);

	default:
		break;
	}

	return -EINVAL;
}