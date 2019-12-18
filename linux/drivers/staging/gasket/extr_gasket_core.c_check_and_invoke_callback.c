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
struct gasket_dev {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
check_and_invoke_callback(struct gasket_dev *gasket_dev,
			  int (*cb_function)(struct gasket_dev *))
{
	int ret = 0;

	if (cb_function) {
		mutex_lock(&gasket_dev->mutex);
		ret = cb_function(gasket_dev);
		mutex_unlock(&gasket_dev->mutex);
	}
	return ret;
}