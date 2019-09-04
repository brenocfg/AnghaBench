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

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmc_refcount ; 
 int /*<<< orphan*/  pmc_reserve_mutex ; 
 int /*<<< orphan*/  reserve_ds_buffers () ; 
 int /*<<< orphan*/  reserve_pmc_hardware () ; 

int x86_reserve_hardware(void)
{
	int err = 0;

	if (!atomic_inc_not_zero(&pmc_refcount)) {
		mutex_lock(&pmc_reserve_mutex);
		if (atomic_read(&pmc_refcount) == 0) {
			if (!reserve_pmc_hardware())
				err = -EBUSY;
			else
				reserve_ds_buffers();
		}
		if (!err)
			atomic_inc(&pmc_refcount);
		mutex_unlock(&pmc_reserve_mutex);
	}

	return err;
}