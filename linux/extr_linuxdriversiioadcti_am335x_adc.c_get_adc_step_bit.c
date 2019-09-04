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
struct tiadc_device {int* channel_step; } ;

/* Variables and functions */

__attribute__((used)) static u32 get_adc_step_bit(struct tiadc_device *adc_dev, int chan)
{
	return 1 << adc_dev->channel_step[chan];
}