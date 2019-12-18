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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned int u32 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct elan_tp_data {unsigned int max_x; unsigned int max_y; unsigned int width_x; unsigned int width_y; unsigned int x_res; unsigned int y_res; int clickpad; int middle_button; struct i2c_client* client; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_max ) (struct i2c_client*,unsigned int*,unsigned int*) ;int (* get_num_traces ) (struct i2c_client*,unsigned int*,unsigned int*) ;int (* get_resolution ) (struct i2c_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ device_property_read_bool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ device_property_read_u32 (int /*<<< orphan*/ *,char*,unsigned int*) ; 
 void* elan_convert_resolution (int /*<<< orphan*/ ) ; 
 int stub1 (struct i2c_client*,unsigned int*,unsigned int*) ; 
 int stub2 (struct i2c_client*,unsigned int*,unsigned int*) ; 
 int stub3 (struct i2c_client*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int elan_query_device_parameters(struct elan_tp_data *data)
{
	struct i2c_client *client = data->client;
	unsigned int x_traces, y_traces;
	u32 x_mm, y_mm;
	u8 hw_x_res, hw_y_res;
	int error;

	if (device_property_read_u32(&client->dev,
				     "touchscreen-size-x", &data->max_x) ||
	    device_property_read_u32(&client->dev,
				     "touchscreen-size-y", &data->max_y)) {
		error = data->ops->get_max(data->client,
					   &data->max_x,
					   &data->max_y);
		if (error)
			return error;
	} else {
		/* size is the maximum + 1 */
		--data->max_x;
		--data->max_y;
	}

	if (device_property_read_u32(&client->dev,
				     "elan,x_traces",
				     &x_traces) ||
	    device_property_read_u32(&client->dev,
				     "elan,y_traces",
				     &y_traces)) {
		error = data->ops->get_num_traces(data->client,
						  &x_traces, &y_traces);
		if (error)
			return error;
	}
	data->width_x = data->max_x / x_traces;
	data->width_y = data->max_y / y_traces;

	if (device_property_read_u32(&client->dev,
				     "touchscreen-x-mm", &x_mm) ||
	    device_property_read_u32(&client->dev,
				     "touchscreen-y-mm", &y_mm)) {
		error = data->ops->get_resolution(data->client,
						  &hw_x_res, &hw_y_res);
		if (error)
			return error;

		data->x_res = elan_convert_resolution(hw_x_res);
		data->y_res = elan_convert_resolution(hw_y_res);
	} else {
		data->x_res = (data->max_x + 1) / x_mm;
		data->y_res = (data->max_y + 1) / y_mm;
	}

	if (device_property_read_bool(&client->dev, "elan,clickpad"))
		data->clickpad = 1;

	if (device_property_read_bool(&client->dev, "elan,middle-button"))
		data->middle_button = true;

	return 0;
}