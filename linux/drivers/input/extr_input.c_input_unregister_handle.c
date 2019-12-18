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
struct input_handle {int /*<<< orphan*/  d_node; int /*<<< orphan*/  h_node; struct input_dev* dev; } ;
struct input_dev {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void input_unregister_handle(struct input_handle *handle)
{
	struct input_dev *dev = handle->dev;

	list_del_rcu(&handle->h_node);

	/*
	 * Take dev->mutex to prevent race with input_release_device().
	 */
	mutex_lock(&dev->mutex);
	list_del_rcu(&handle->d_node);
	mutex_unlock(&dev->mutex);

	synchronize_rcu();
}