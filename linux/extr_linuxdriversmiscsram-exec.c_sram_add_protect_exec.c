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
struct sram_partition {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  exec_pool_list ; 
 int /*<<< orphan*/  exec_pool_list_mutex ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int sram_add_protect_exec(struct sram_partition *part)
{
	mutex_lock(&exec_pool_list_mutex);
	list_add_tail(&part->list, &exec_pool_list);
	mutex_unlock(&exec_pool_list_mutex);

	return 0;
}