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
 unsigned long long MAX_PHYSMEM_BITS ; 
 int /*<<< orphan*/  ehea_busmap_mutex ; 
 int /*<<< orphan*/  ehea_create_busmap_callback ; 
 scalar_t__ ehea_mr_len ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int walk_system_ram_range (int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int ehea_create_busmap(void)
{
	int ret;

	mutex_lock(&ehea_busmap_mutex);
	ehea_mr_len = 0;
	ret = walk_system_ram_range(0, 1ULL << MAX_PHYSMEM_BITS, NULL,
				   ehea_create_busmap_callback);
	mutex_unlock(&ehea_busmap_mutex);
	return ret;
}