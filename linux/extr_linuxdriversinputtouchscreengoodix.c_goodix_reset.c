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
struct goodix_ts_data {int /*<<< orphan*/  gpiod_rst; TYPE_1__* client; int /*<<< orphan*/  gpiod_int; } ;
struct TYPE_2__ {int addr; } ;

/* Variables and functions */
 int goodix_int_sync (struct goodix_ts_data*) ; 
 int gpiod_direction_input (int /*<<< orphan*/ ) ; 
 int gpiod_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int goodix_reset(struct goodix_ts_data *ts)
{
	int error;

	/* begin select I2C slave addr */
	error = gpiod_direction_output(ts->gpiod_rst, 0);
	if (error)
		return error;

	msleep(20);				/* T2: > 10ms */

	/* HIGH: 0x28/0x29, LOW: 0xBA/0xBB */
	error = gpiod_direction_output(ts->gpiod_int, ts->client->addr == 0x14);
	if (error)
		return error;

	usleep_range(100, 2000);		/* T3: > 100us */

	error = gpiod_direction_output(ts->gpiod_rst, 1);
	if (error)
		return error;

	usleep_range(6000, 10000);		/* T4: > 5ms */

	/* end select I2C slave addr */
	error = gpiod_direction_input(ts->gpiod_rst);
	if (error)
		return error;

	error = goodix_int_sync(ts);
	if (error)
		return error;

	return 0;
}