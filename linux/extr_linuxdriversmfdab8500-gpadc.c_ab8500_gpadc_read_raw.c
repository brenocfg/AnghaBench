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
typedef  int /*<<< orphan*/  u8 ;
struct ab8500_gpadc {int dummy; } ;

/* Variables and functions */
 int ab8500_gpadc_double_read_raw (struct ab8500_gpadc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ab8500_gpadc_read_raw(struct ab8500_gpadc *gpadc, u8 channel,
		u8 avg_sample, u8 trig_edge, u8 trig_timer, u8 conv_type)
{
	return ab8500_gpadc_double_read_raw(gpadc, channel, avg_sample,
					    trig_edge, trig_timer, conv_type,
					    NULL);
}