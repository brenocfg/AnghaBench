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
struct ltc2485_data {int /*<<< orphan*/  time_prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get () ; 
 unsigned int ktime_ms_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (unsigned int const) ; 

__attribute__((used)) static void ltc2485_wait_conv(struct ltc2485_data *data)
{
	const unsigned int conv_time = 147;	/* conversion time ms */
	unsigned int time_elapsed;

	/* delay if conversion time not passed since last read or write */
	time_elapsed = ktime_ms_delta(ktime_get(), data->time_prev);

	if (time_elapsed < conv_time)
		msleep(conv_time - time_elapsed);
}