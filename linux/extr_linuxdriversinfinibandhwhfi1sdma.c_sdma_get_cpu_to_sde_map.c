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
struct sdma_engine {int /*<<< orphan*/  cpu_mask; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  cpumap_print_to_pagebuf (int,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_to_sde_mutex ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strnlen (char*,int /*<<< orphan*/ ) ; 

ssize_t sdma_get_cpu_to_sde_map(struct sdma_engine *sde, char *buf)
{
	mutex_lock(&process_to_sde_mutex);
	if (cpumask_empty(&sde->cpu_mask))
		snprintf(buf, PAGE_SIZE, "%s\n", "empty");
	else
		cpumap_print_to_pagebuf(true, buf, &sde->cpu_mask);
	mutex_unlock(&process_to_sde_mutex);
	return strnlen(buf, PAGE_SIZE);
}