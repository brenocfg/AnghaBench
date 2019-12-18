#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct i2c_msg {int flags; scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct gb_operation {TYPE_2__* request; } ;
struct gb_i2c_transfer_request {struct gb_i2c_transfer_op* ops; int /*<<< orphan*/  op_count; } ;
struct gb_i2c_transfer_op {int dummy; } ;
struct gb_i2c_device {TYPE_1__* gbphy_dev; } ;
struct gb_connection {int dummy; } ;
struct TYPE_4__ {struct gb_i2c_transfer_request* payload; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_I2C_TYPE_TRANSFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_M_RD ; 
 scalar_t__ U16_MAX ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 struct gb_i2c_device* gb_connection_get_data (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_i2c_fill_transfer_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct gb_operation* gb_operation_create (struct gb_connection*,int /*<<< orphan*/ ,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct gb_operation *
gb_i2c_operation_create(struct gb_connection *connection,
			struct i2c_msg *msgs, u32 msg_count)
{
	struct gb_i2c_device *gb_i2c_dev = gb_connection_get_data(connection);
	struct gb_i2c_transfer_request *request;
	struct gb_operation *operation;
	struct gb_i2c_transfer_op *op;
	struct i2c_msg *msg;
	u32 data_out_size = 0;
	u32 data_in_size = 0;
	size_t request_size;
	void *data;
	u16 op_count;
	u32 i;

	if (msg_count > (u32)U16_MAX) {
		dev_err(&gb_i2c_dev->gbphy_dev->dev, "msg_count (%u) too big\n",
			msg_count);
		return NULL;
	}
	op_count = (u16)msg_count;

	/*
	 * In addition to space for all message descriptors we need
	 * to have enough to hold all outbound message data.
	 */
	msg = msgs;
	for (i = 0; i < msg_count; i++, msg++)
		if (msg->flags & I2C_M_RD)
			data_in_size += (u32)msg->len;
		else
			data_out_size += (u32)msg->len;

	request_size = sizeof(*request);
	request_size += msg_count * sizeof(*op);
	request_size += data_out_size;

	/* Response consists only of incoming data */
	operation = gb_operation_create(connection, GB_I2C_TYPE_TRANSFER,
					request_size, data_in_size, GFP_KERNEL);
	if (!operation)
		return NULL;

	request = operation->request->payload;
	request->op_count = cpu_to_le16(op_count);
	/* Fill in the ops array */
	op = &request->ops[0];
	msg = msgs;
	for (i = 0; i < msg_count; i++)
		gb_i2c_fill_transfer_op(op++, msg++);

	if (!data_out_size)
		return operation;

	/* Copy over the outgoing data; it starts after the last op */
	data = op;
	msg = msgs;
	for (i = 0; i < msg_count; i++) {
		if (!(msg->flags & I2C_M_RD)) {
			memcpy(data, msg->buf, msg->len);
			data += msg->len;
		}
		msg++;
	}

	return operation;
}