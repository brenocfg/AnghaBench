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
typedef  unsigned int u8 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETP_I2C_XY_TRACENUM_CMD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int elan_i2c_read_cmd (struct i2c_client*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int elan_i2c_get_num_traces(struct i2c_client *client,
				   unsigned int *x_traces,
				   unsigned int *y_traces)
{
	int error;
	u8 val[3];

	error = elan_i2c_read_cmd(client, ETP_I2C_XY_TRACENUM_CMD, val);
	if (error) {
		dev_err(&client->dev, "failed to get trace info: %d\n", error);
		return error;
	}

	*x_traces = val[0];
	*y_traces = val[1];

	return 0;
}