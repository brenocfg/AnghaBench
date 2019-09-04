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
struct rohm_ts_data {int initialized; int /*<<< orphan*/  client; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct rohm_ts_data* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  rohm_ts_power_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rohm_ts_close(struct input_dev *input_dev)
{
	struct rohm_ts_data *ts = input_get_drvdata(input_dev);

	rohm_ts_power_off(ts->client);

	ts->initialized = false;
}