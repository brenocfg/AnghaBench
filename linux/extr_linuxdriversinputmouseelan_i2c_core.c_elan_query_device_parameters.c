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
struct elan_tp_data {unsigned int max_x; unsigned int max_y; unsigned int width_x; unsigned int width_y; void* y_res; void* x_res; int /*<<< orphan*/  client; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_max ) (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ;int (* get_num_traces ) (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ;int (* get_resolution ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 void* elan_convert_resolution (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int stub2 (int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int elan_query_device_parameters(struct elan_tp_data *data)
{
	unsigned int x_traces, y_traces;
	u8 hw_x_res, hw_y_res;
	int error;

	error = data->ops->get_max(data->client, &data->max_x, &data->max_y);
	if (error)
		return error;

	error = data->ops->get_num_traces(data->client, &x_traces, &y_traces);
	if (error)
		return error;

	data->width_x = data->max_x / x_traces;
	data->width_y = data->max_y / y_traces;

	error = data->ops->get_resolution(data->client, &hw_x_res, &hw_y_res);
	if (error)
		return error;

	data->x_res = elan_convert_resolution(hw_x_res);
	data->y_res = elan_convert_resolution(hw_y_res);

	return 0;
}