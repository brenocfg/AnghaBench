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
struct goodix_ts_data {int /*<<< orphan*/  gpiod_int; } ;

/* Variables and functions */
 int gpiod_direction_input (int /*<<< orphan*/ ) ; 
 int gpiod_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int goodix_int_sync(struct goodix_ts_data *ts)
{
	int error;

	error = gpiod_direction_output(ts->gpiod_int, 0);
	if (error)
		return error;

	msleep(50);				/* T5: 50ms */

	error = gpiod_direction_input(ts->gpiod_int);
	if (error)
		return error;

	return 0;
}