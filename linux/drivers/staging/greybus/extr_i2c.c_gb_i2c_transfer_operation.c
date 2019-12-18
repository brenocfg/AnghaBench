#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct i2c_msg {int dummy; } ;
struct gb_operation {TYPE_1__* response; } ;
struct gb_i2c_transfer_response {int dummy; } ;
struct gb_i2c_device {TYPE_2__* gbphy_dev; struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device dev; } ;
struct TYPE_4__ {struct gb_i2c_transfer_response* payload; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  gb_i2c_decode_response (struct i2c_msg*,int,struct gb_i2c_transfer_response*) ; 
 int /*<<< orphan*/  gb_i2c_expected_transfer_error (int) ; 
 struct gb_operation* gb_i2c_operation_create (struct gb_connection*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  gb_operation_put (struct gb_operation*) ; 
 int gb_operation_request_send_sync (struct gb_operation*) ; 
 int gbphy_runtime_get_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  gbphy_runtime_put_autosuspend (TYPE_2__*) ; 

__attribute__((used)) static int gb_i2c_transfer_operation(struct gb_i2c_device *gb_i2c_dev,
				     struct i2c_msg *msgs, u32 msg_count)
{
	struct gb_connection *connection = gb_i2c_dev->connection;
	struct device *dev = &gb_i2c_dev->gbphy_dev->dev;
	struct gb_operation *operation;
	int ret;

	operation = gb_i2c_operation_create(connection, msgs, msg_count);
	if (!operation)
		return -ENOMEM;

	ret = gbphy_runtime_get_sync(gb_i2c_dev->gbphy_dev);
	if (ret)
		goto exit_operation_put;

	ret = gb_operation_request_send_sync(operation);
	if (!ret) {
		struct gb_i2c_transfer_response *response;

		response = operation->response->payload;
		gb_i2c_decode_response(msgs, msg_count, response);
		ret = msg_count;
	} else if (!gb_i2c_expected_transfer_error(ret)) {
		dev_err(dev, "transfer operation failed (%d)\n", ret);
	}

	gbphy_runtime_put_autosuspend(gb_i2c_dev->gbphy_dev);

exit_operation_put:
	gb_operation_put(operation);

	return ret;
}