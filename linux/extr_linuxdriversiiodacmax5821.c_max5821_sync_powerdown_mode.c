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
struct max5821_data {int* powerdown_mode; int /*<<< orphan*/  client; scalar_t__* powerdown; } ;
struct iio_chan_spec {size_t channel; } ;

/* Variables and functions */
 int MAX5821_EXTENDED_COMMAND_MODE ; 
 int MAX5821_EXTENDED_DAC_A ; 
 int MAX5821_EXTENDED_DAC_B ; 
 int MAX5821_EXTENDED_POWER_UP ; 
 int i2c_master_send (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int max5821_sync_powerdown_mode(struct max5821_data *data,
				       const struct iio_chan_spec *chan)
{
	u8 outbuf[2];

	outbuf[0] = MAX5821_EXTENDED_COMMAND_MODE;

	if (chan->channel == 0)
		outbuf[1] = MAX5821_EXTENDED_DAC_A;
	else
		outbuf[1] = MAX5821_EXTENDED_DAC_B;

	if (data->powerdown[chan->channel])
		outbuf[1] |= data->powerdown_mode[chan->channel] + 1;
	else
		outbuf[1] |= MAX5821_EXTENDED_POWER_UP;

	return i2c_master_send(data->client, outbuf, 2);
}