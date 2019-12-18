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
struct be_adapter {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  _be_roce_dev_remove (struct be_adapter*) ; 
 int /*<<< orphan*/  be_adapter_list_lock ; 
 scalar_t__ be_roce_supported (struct be_adapter*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void be_roce_dev_remove(struct be_adapter *adapter)
{
	if (be_roce_supported(adapter)) {
		mutex_lock(&be_adapter_list_lock);
		_be_roce_dev_remove(adapter);
		list_del(&adapter->entry);
		mutex_unlock(&be_adapter_list_lock);
	}
}