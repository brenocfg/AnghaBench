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
struct i2c_client {int dummy; } ;
struct ads1015_data {scalar_t__ id; TYPE_1__* channel_data; } ;
typedef  int s16 ;
struct TYPE_2__ {unsigned int pga; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int const) ; 
 scalar_t__ ads1115 ; 
 int* fullscale_table ; 
 struct ads1015_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int ads1015_reg_to_mv(struct i2c_client *client, unsigned int channel,
			     s16 reg)
{
	struct ads1015_data *data = i2c_get_clientdata(client);
	unsigned int pga = data->channel_data[channel].pga;
	int fullscale = fullscale_table[pga];
	const int mask = data->id == ads1115 ? 0x7fff : 0x7ff0;

	return DIV_ROUND_CLOSEST(reg * fullscale, mask);
}