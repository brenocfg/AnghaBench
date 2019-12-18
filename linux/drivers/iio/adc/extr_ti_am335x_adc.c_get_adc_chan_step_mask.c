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
typedef  int u32 ;
struct tiadc_device {int* channel_step; scalar_t__* channel_line; } ;
struct iio_chan_spec {scalar_t__ channel; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static u32 get_adc_chan_step_mask(struct tiadc_device *adc_dev,
		struct iio_chan_spec const *chan)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(adc_dev->channel_step); i++) {
		if (chan->channel == adc_dev->channel_line[i]) {
			u32 step;

			step = adc_dev->channel_step[i];
			/* +1 for the charger */
			return 1 << (step + 1);
		}
	}
	WARN_ON(1);
	return 0;
}