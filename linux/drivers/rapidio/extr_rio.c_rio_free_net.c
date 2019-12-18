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
struct rio_net {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* release ) (struct rio_net*) ;int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rio_global_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rio_net*) ; 

void rio_free_net(struct rio_net *net)
{
	spin_lock(&rio_global_list_lock);
	if (!list_empty(&net->node))
		list_del(&net->node);
	spin_unlock(&rio_global_list_lock);
	if (net->release)
		net->release(net);
	device_unregister(&net->dev);
}