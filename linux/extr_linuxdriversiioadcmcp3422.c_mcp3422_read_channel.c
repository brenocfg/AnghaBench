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
struct mcp3422 {size_t config; int /*<<< orphan*/ * pga; } ;
struct iio_chan_spec {size_t channel; } ;

/* Variables and functions */
 size_t MCP3422_CHANNEL (size_t) ; 
 size_t MCP3422_CHANNEL_MASK ; 
 size_t MCP3422_CHANNEL_VALUE (size_t) ; 
 size_t MCP3422_PGA_MASK ; 
 size_t MCP3422_PGA_VALUE (int /*<<< orphan*/ ) ; 
 size_t MCP3422_SAMPLE_RATE (size_t) ; 
 int mcp3422_read (struct mcp3422*,int*,size_t*) ; 
 int /*<<< orphan*/ * mcp3422_read_times ; 
 int mcp3422_update_config (struct mcp3422*,size_t) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mcp3422_read_channel(struct mcp3422 *adc,
				struct iio_chan_spec const *channel, int *value)
{
	int ret;
	u8 config;
	u8 req_channel = channel->channel;

	if (req_channel != MCP3422_CHANNEL(adc->config)) {
		config = adc->config;
		config &= ~MCP3422_CHANNEL_MASK;
		config |= MCP3422_CHANNEL_VALUE(req_channel);
		config &= ~MCP3422_PGA_MASK;
		config |= MCP3422_PGA_VALUE(adc->pga[req_channel]);
		ret = mcp3422_update_config(adc, config);
		if (ret < 0)
			return ret;
		msleep(mcp3422_read_times[MCP3422_SAMPLE_RATE(adc->config)]);
	}

	return mcp3422_read(adc, value, &config);
}