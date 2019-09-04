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
struct xilly_endpoint {int /*<<< orphan*/  ep_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ep_list_lock ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xilly_quiesce (struct xilly_endpoint*) ; 
 int /*<<< orphan*/  xillybus_cleanup_chrdev (struct xilly_endpoint*) ; 
 int /*<<< orphan*/  xillybus_wq ; 

void xillybus_endpoint_remove(struct xilly_endpoint *endpoint)
{
	xillybus_cleanup_chrdev(endpoint);

	mutex_lock(&ep_list_lock);
	list_del(&endpoint->ep_list);
	mutex_unlock(&ep_list_lock);

	xilly_quiesce(endpoint);

	/*
	 * Flushing is done upon endpoint release to prevent access to memory
	 * just about to be released. This makes the quiesce complete.
	 */
	flush_workqueue(xillybus_wq);
}