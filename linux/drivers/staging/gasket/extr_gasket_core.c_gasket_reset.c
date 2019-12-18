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
 int gasket_reset_nolock (struct gasket_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int gasket_reset(struct gasket_dev *gasket_dev)
{
	int ret;

	mutex_lock(&gasket_dev->mutex);
	ret = gasket_reset_nolock(gasket_dev);
	mutex_unlock(&gasket_dev->mutex);
	return ret;
}