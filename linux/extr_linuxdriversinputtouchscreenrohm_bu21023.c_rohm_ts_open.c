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
struct rohm_ts_data {int initialized; int /*<<< orphan*/  setup2; struct i2c_client* client; } ;
struct input_dev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct rohm_ts_data* input_get_drvdata (struct input_dev*) ; 
 int rohm_ts_device_init (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rohm_ts_open(struct input_dev *input_dev)
{
	struct rohm_ts_data *ts = input_get_drvdata(input_dev);
	struct i2c_client *client = ts->client;
	int error;

	if (!ts->initialized) {
		error = rohm_ts_device_init(client, ts->setup2);
		if (error) {
			dev_err(&client->dev,
				"device initialization failed: %d\n", error);
			return error;
		}

		ts->initialized = true;
	}

	return 0;
}