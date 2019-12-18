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
struct rio_net {int /*<<< orphan*/  node; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int device_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rio_global_list_lock ; 
 int /*<<< orphan*/  rio_nets ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int rio_add_net(struct rio_net *net)
{
	int err;

	err = device_register(&net->dev);
	if (err)
		return err;
	spin_lock(&rio_global_list_lock);
	list_add_tail(&net->node, &rio_nets);
	spin_unlock(&rio_global_list_lock);

	return 0;
}