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
struct miscdevice {int minor; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int DYNAMIC_MINORS ; 
 int /*<<< orphan*/  MISC_MAJOR ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_class ; 
 int /*<<< orphan*/  misc_minors ; 
 int /*<<< orphan*/  misc_mtx ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void misc_deregister(struct miscdevice *misc)
{
	int i = DYNAMIC_MINORS - misc->minor - 1;

	if (WARN_ON(list_empty(&misc->list)))
		return;

	mutex_lock(&misc_mtx);
	list_del(&misc->list);
	device_destroy(misc_class, MKDEV(MISC_MAJOR, misc->minor));
	if (i < DYNAMIC_MINORS && i >= 0)
		clear_bit(i, misc_minors);
	mutex_unlock(&misc_mtx);
}