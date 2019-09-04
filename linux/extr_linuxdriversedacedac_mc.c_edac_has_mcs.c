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
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mc_devices ; 
 int /*<<< orphan*/  mem_ctls_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

bool edac_has_mcs(void)
{
	bool ret;

	mutex_lock(&mem_ctls_mutex);

	ret = list_empty(&mc_devices);

	mutex_unlock(&mem_ctls_mutex);

	return !ret;
}