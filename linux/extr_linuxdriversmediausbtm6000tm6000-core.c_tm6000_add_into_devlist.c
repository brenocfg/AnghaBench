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
struct tm6000_core {int /*<<< orphan*/  devlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tm6000_devlist ; 
 int /*<<< orphan*/  tm6000_devlist_mutex ; 

void tm6000_add_into_devlist(struct tm6000_core *dev)
{
	mutex_lock(&tm6000_devlist_mutex);
	list_add_tail(&dev->devlist, &tm6000_devlist);
	mutex_unlock(&tm6000_devlist_mutex);
}