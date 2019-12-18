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
typedef  int /*<<< orphan*/  u16 ;
struct gb_operation_msg_hdr {int /*<<< orphan*/  type; int /*<<< orphan*/  operation_id; } ;
struct gb_operation {int /*<<< orphan*/  work; int /*<<< orphan*/  request; } ;
struct gb_connection {int /*<<< orphan*/  wq; int /*<<< orphan*/  name; TYPE_1__* hd; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct gb_operation* gb_operation_create_incoming (struct gb_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 
 int gb_operation_get_active (struct gb_operation*) ; 
 int /*<<< orphan*/  gb_operation_put (struct gb_operation*) ; 
 scalar_t__ gb_operation_result_set (struct gb_operation*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_gb_message_recv_request (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gb_connection_recv_request(struct gb_connection *connection,
				const struct gb_operation_msg_hdr *header,
				void *data, size_t size)
{
	struct gb_operation *operation;
	u16 operation_id;
	u8 type;
	int ret;

	operation_id = le16_to_cpu(header->operation_id);
	type = header->type;

	operation = gb_operation_create_incoming(connection, operation_id,
						 type, data, size);
	if (!operation) {
		dev_err(&connection->hd->dev,
			"%s: can't create incoming operation\n",
			connection->name);
		return;
	}

	ret = gb_operation_get_active(operation);
	if (ret) {
		gb_operation_put(operation);
		return;
	}
	trace_gb_message_recv_request(operation->request);

	/*
	 * The initial reference to the operation will be dropped when the
	 * request handler returns.
	 */
	if (gb_operation_result_set(operation, -EINPROGRESS))
		queue_work(connection->wq, &operation->work);
}