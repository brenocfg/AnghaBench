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
struct input_handler {int /*<<< orphan*/  (* start ) (struct input_handle*) ;int /*<<< orphan*/  h_list; scalar_t__ filter; } ;
struct input_handle {int /*<<< orphan*/  h_node; int /*<<< orphan*/  d_node; struct input_dev* dev; struct input_handler* handler; } ;
struct input_dev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  h_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct input_handle*) ; 

int input_register_handle(struct input_handle *handle)
{
	struct input_handler *handler = handle->handler;
	struct input_dev *dev = handle->dev;
	int error;

	/*
	 * We take dev->mutex here to prevent race with
	 * input_release_device().
	 */
	error = mutex_lock_interruptible(&dev->mutex);
	if (error)
		return error;

	/*
	 * Filters go to the head of the list, normal handlers
	 * to the tail.
	 */
	if (handler->filter)
		list_add_rcu(&handle->d_node, &dev->h_list);
	else
		list_add_tail_rcu(&handle->d_node, &dev->h_list);

	mutex_unlock(&dev->mutex);

	/*
	 * Since we are supposed to be called from ->connect()
	 * which is mutually exclusive with ->disconnect()
	 * we can't be racing with input_unregister_handle()
	 * and so separate lock is not needed here.
	 */
	list_add_tail_rcu(&handle->h_node, &handler->h_list);

	if (handler->start)
		handler->start(handle);

	return 0;
}