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
struct gadget_info {int /*<<< orphan*/  lock; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct gadget_info* to_gadget_info (struct config_item*) ; 
 int /*<<< orphan*/  unregister_gadget (struct gadget_info*) ; 

void unregister_gadget_item(struct config_item *item)
{
	struct gadget_info *gi = to_gadget_info(item);

	mutex_lock(&gi->lock);
	unregister_gadget(gi);
	mutex_unlock(&gi->lock);
}