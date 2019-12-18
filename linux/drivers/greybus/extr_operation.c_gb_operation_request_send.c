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
typedef  scalar_t__ u16 ;
struct gb_operation_msg_hdr {int /*<<< orphan*/  operation_id; } ;
struct TYPE_4__ {scalar_t__ expires; } ;
struct gb_operation {TYPE_2__ timer; TYPE_1__* request; scalar_t__ id; scalar_t__ callback; struct gb_connection* connection; } ;
struct gb_connection {int /*<<< orphan*/  op_cycle; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  scalar_t__ gb_operation_callback ;
struct TYPE_3__ {struct gb_operation_msg_hdr* header; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EINPROGRESS ; 
 int EINVAL ; 
 unsigned int U16_MAX ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 scalar_t__ gb_connection_is_offloaded (struct gb_connection*) ; 
 int gb_message_send (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_operation_get (struct gb_operation*) ; 
 int gb_operation_get_active (struct gb_operation*) ; 
 scalar_t__ gb_operation_is_unidirectional (struct gb_operation*) ; 
 int /*<<< orphan*/  gb_operation_put (struct gb_operation*) ; 
 int /*<<< orphan*/  gb_operation_put_active (struct gb_operation*) ; 
 int /*<<< orphan*/  gb_operation_result_set (struct gb_operation*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (unsigned int) ; 

int gb_operation_request_send(struct gb_operation *operation,
			      gb_operation_callback callback,
			      unsigned int timeout,
			      gfp_t gfp)
{
	struct gb_connection *connection = operation->connection;
	struct gb_operation_msg_hdr *header;
	unsigned int cycle;
	int ret;

	if (gb_connection_is_offloaded(connection))
		return -EBUSY;

	if (!callback)
		return -EINVAL;

	/*
	 * Record the callback function, which is executed in
	 * non-atomic (workqueue) context when the final result
	 * of an operation has been set.
	 */
	operation->callback = callback;

	/*
	 * Assign the operation's id, and store it in the request header.
	 * Zero is a reserved operation id for unidirectional operations.
	 */
	if (gb_operation_is_unidirectional(operation)) {
		operation->id = 0;
	} else {
		cycle = (unsigned int)atomic_inc_return(&connection->op_cycle);
		operation->id = (u16)(cycle % U16_MAX + 1);
	}

	header = operation->request->header;
	header->operation_id = cpu_to_le16(operation->id);

	gb_operation_result_set(operation, -EINPROGRESS);

	/*
	 * Get an extra reference on the operation. It'll be dropped when the
	 * operation completes.
	 */
	gb_operation_get(operation);
	ret = gb_operation_get_active(operation);
	if (ret)
		goto err_put;

	ret = gb_message_send(operation->request, gfp);
	if (ret)
		goto err_put_active;

	if (timeout) {
		operation->timer.expires = jiffies + msecs_to_jiffies(timeout);
		add_timer(&operation->timer);
	}

	return 0;

err_put_active:
	gb_operation_put_active(operation);
err_put:
	gb_operation_put(operation);

	return ret;
}