#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u16 ;
struct dac5571_data {unsigned int* buf; int /*<<< orphan*/  client; TYPE_1__* spec; } ;
struct TYPE_2__ {int resolution; } ;

/* Variables and functions */
 int DAC5571_CHANNEL_SELECT ; 
 int DAC5571_LOADMODE_DIRECT ; 
 int EIO ; 
 int i2c_master_send (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int dac5571_cmd_quad(struct dac5571_data *data, int channel, u16 val)
{
	unsigned int shift;

	shift = 16 - data->spec->resolution;
	data->buf[2] = val << shift;
	data->buf[1] = (val >> (8 - shift));
	data->buf[0] = (channel << DAC5571_CHANNEL_SELECT) |
		       DAC5571_LOADMODE_DIRECT;

	if (i2c_master_send(data->client, data->buf, 3) != 3)
		return -EIO;

	return 0;
}