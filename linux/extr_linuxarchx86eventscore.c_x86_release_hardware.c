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
 scalar_t__ atomic_dec_and_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmc_refcount ; 
 int /*<<< orphan*/  pmc_reserve_mutex ; 
 int /*<<< orphan*/  release_ds_buffers () ; 
 int /*<<< orphan*/  release_pmc_hardware () ; 

void x86_release_hardware(void)
{
	if (atomic_dec_and_mutex_lock(&pmc_refcount, &pmc_reserve_mutex)) {
		release_pmc_hardware();
		release_ds_buffers();
		mutex_unlock(&pmc_reserve_mutex);
	}
}