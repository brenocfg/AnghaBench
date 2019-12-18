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
struct gb_operation {int /*<<< orphan*/  links; int /*<<< orphan*/  active; struct gb_connection* connection; } ;
struct gb_connection {int state; int /*<<< orphan*/  lock; int /*<<< orphan*/  operations; } ;

/* Variables and functions */
 int ENOTCONN ; 
#define  GB_CONNECTION_STATE_DISCONNECTING 130 
#define  GB_CONNECTION_STATE_ENABLED 129 
#define  GB_CONNECTION_STATE_ENABLED_TX 128 
 int /*<<< orphan*/  gb_operation_is_core (struct gb_operation*) ; 
 int /*<<< orphan*/  gb_operation_is_incoming (struct gb_operation*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_gb_operation_get_active (struct gb_operation*) ; 

__attribute__((used)) static int gb_operation_get_active(struct gb_operation *operation)
{
	struct gb_connection *connection = operation->connection;
	unsigned long flags;

	spin_lock_irqsave(&connection->lock, flags);
	switch (connection->state) {
	case GB_CONNECTION_STATE_ENABLED:
		break;
	case GB_CONNECTION_STATE_ENABLED_TX:
		if (gb_operation_is_incoming(operation))
			goto err_unlock;
		break;
	case GB_CONNECTION_STATE_DISCONNECTING:
		if (!gb_operation_is_core(operation))
			goto err_unlock;
		break;
	default:
		goto err_unlock;
	}

	if (operation->active++ == 0)
		list_add_tail(&operation->links, &connection->operations);

	trace_gb_operation_get_active(operation);

	spin_unlock_irqrestore(&connection->lock, flags);

	return 0;

err_unlock:
	spin_unlock_irqrestore(&connection->lock, flags);

	return -ENOTCONN;
}