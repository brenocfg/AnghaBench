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
struct ads1015_data {int* data_rate; TYPE_1__* channel_data; } ;
struct TYPE_2__ {int data_rate; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ads1015_data_rate ; 

__attribute__((used)) static int ads1015_set_data_rate(struct ads1015_data *data, int chan, int rate)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ads1015_data_rate); i++) {
		if (data->data_rate[i] == rate) {
			data->channel_data[chan].data_rate = i;
			return 0;
		}
	}

	return -EINVAL;
}