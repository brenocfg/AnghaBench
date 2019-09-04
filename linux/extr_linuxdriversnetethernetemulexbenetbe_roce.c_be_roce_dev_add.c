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
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _be_roce_dev_add (struct be_adapter*) ; 
 int /*<<< orphan*/  be_adapter_list ; 
 int /*<<< orphan*/  be_adapter_list_lock ; 
 scalar_t__ be_roce_supported (struct be_adapter*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void be_roce_dev_add(struct be_adapter *adapter)
{
	if (be_roce_supported(adapter)) {
		INIT_LIST_HEAD(&adapter->entry);
		mutex_lock(&be_adapter_list_lock);
		list_add_tail(&adapter->entry, &be_adapter_list);

		/* invoke add() routine of roce driver only if
		 * valid driver registered with add method and add() is not yet
		 * invoked on a given adapter.
		 */
		_be_roce_dev_add(adapter);
		mutex_unlock(&be_adapter_list_lock);
	}
}